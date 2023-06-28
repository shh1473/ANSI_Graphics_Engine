#include "ansi_geometry.h"

#include "core/log/ansi_log.h"
#include "resource/vertex_array/ansi_vertex_array.h"
#include "utility/obj_loader/ansi_obj_loader.h"

namespace AN
{

	Geometry::Geometry() :
		m_isIncludeTB(false),
		m_vertexCount(0),
		m_indexCount(0),
		m_vertexBufferId(0),
		m_indexBufferId(0),
		m_vertexArrays()
	{

	}

	Geometry::~Geometry()
	{
		if (m_vertexBufferId) {
			GL_ERROR_LOG(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GL_ERROR_LOG(glDeleteBuffers(1, &m_vertexBufferId));
		}
		if (m_indexBufferId) {
			GL_ERROR_LOG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			GL_ERROR_LOG(glDeleteBuffers(1, &m_indexBufferId));
		}
		for (auto & vertexArray : m_vertexArrays) {
			AN_DELETE(vertexArray);
		}
	}

	VertexArray * Geometry::GenerateVertexArray(unsigned flag)
	{
		if (!m_vertexCount)
		{
			AN_ERROR_LOG(L"아직 지오메트리를 생성하지 않았습니다.");
			return nullptr;
		}

		unsigned id{ 0 };
		GL_CHECK_NULL(glGenVertexArrays(1, &id));
		GL_CHECK_NULL(glBindVertexArray(id));
		GL_CHECK_NULL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));

		unsigned offset{ 0 };
		unsigned stride{ 0 };
		std::vector<unsigned> elementCounts;

		if (flag & POSITION) { elementCounts.push_back(3); stride += 3 * sizeof(float); }
		if (flag & TEXCOORD) { elementCounts.push_back(2); stride += 2 * sizeof(float); }
		if (flag & NORMAL) { elementCounts.push_back(3); stride += 3 * sizeof(float); }
		if (flag & TANGENTBINORMAL)
		{
			elementCounts.push_back(3);
			elementCounts.push_back(3);
			stride += 6 * sizeof(float);
		}

		for (unsigned i{ 0 }; i < elementCounts.size(); ++i)
		{
			GL_CHECK_NULL(glEnableVertexAttribArray(i));
			GL_CHECK_NULL(glVertexAttribPointer(i, elementCounts[i], GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>(offset)));
			offset += elementCounts[i] * sizeof(float);
		}

		m_vertexArrays.push_back(new VertexArray(id));
		return m_vertexArrays.back();
	}

	bool Geometry::CreateCube(float width, float height, float depth, unsigned widthDivision, unsigned heightDivision, unsigned depthDivision, bool isIncludeTB)
	{
		AN_CHECK_LOG_M(m_vertexCount == 0, L"이미 지오메트리를 생성했습니다.");
		m_isIncludeTB = isIncludeTB;

		unsigned currentVertexCount{ 0 };
		std::vector<float> rawVerticesData;
		std::vector<unsigned> rawIndicesData;
		rawVerticesData.reserve((
			(widthDivision + 1) * (heightDivision + 1) + (widthDivision + 1) * (heightDivision + 1) +
			(widthDivision + 1) * (depthDivision + 1) + (widthDivision + 1) * (depthDivision + 1) +
			(depthDivision + 1) * (heightDivision + 1) + (depthDivision + 1) * (heightDivision + 1)) * (m_isIncludeTB ? 14 : 8));
		rawIndicesData.reserve((
			widthDivision * heightDivision + widthDivision * heightDivision +
			widthDivision * depthDivision + widthDivision * depthDivision +
			depthDivision * heightDivision + depthDivision * heightDivision) * 6);

		currentVertexCount += BuildPlane(0, 1, 2,  1, -1, width, height, depth, widthDivision, heightDivision, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 1, 2, -1, -1, width, height, -depth, widthDivision, heightDivision, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 2, 1,  1,  1, width, depth, height, widthDivision, depthDivision, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 2, 1,  1, -1, width, depth, -height, widthDivision, depthDivision, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(2, 1, 0, -1, -1, depth, height, width, depthDivision, heightDivision, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(2, 1, 0,  1, -1, depth, height, -width, depthDivision, heightDivision, currentVertexCount, rawVerticesData, rawIndicesData);

		GL_CHECK(glGenBuffers(1, &m_vertexBufferId));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), rawVerticesData.data(), GL_STATIC_DRAW));

		GL_CHECK(glGenBuffers(1, &m_indexBufferId));
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId));
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndicesData.size() * sizeof(unsigned), rawIndicesData.data(), GL_STATIC_DRAW));

		return true;
	}

	bool Geometry::LoadFromObj(const std::string & filePath, bool isIncludeTB)
	{
		AN_CHECK_LOG_M(m_vertexCount == 0, L"이미 지오메트리를 생성했습니다.");
		AN_CHECK(ObjLoader::LoadObj(filePath, isIncludeTB, m_vertexBufferId, m_vertexCount));

		return true;
	}

	unsigned Geometry::BuildPlane(
		unsigned uIndex, unsigned vIndex, unsigned wIndex, float uDirection, float vDirection,
		float width, float height, float depth, unsigned divisionX, unsigned divisionY,
		unsigned currentVertexCount, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData)
	{
		unsigned vertexCount{ 0 };
		const float segmentWidth{ width / static_cast<float>(divisionX) };
		const float segmentHeight{ height / static_cast<float>(divisionY) };
		const float halfWidth{ width * 0.5f };
		const float halfHeight{ height * 0.5f };
		const float halfDepth{ depth * 0.5f };
		glm::vec3 tmpVector(0.0f);

		for (unsigned i{ 0 }; i < divisionY + 1; ++i)
		{
			for (unsigned j{ 0 }; j < divisionX + 1; ++j)
			{
				tmpVector[uIndex] = j * segmentWidth - halfWidth * uDirection;
				tmpVector[vIndex] = i * segmentHeight - halfHeight * vDirection;
				tmpVector[wIndex] = halfDepth;
				rawVerticesData.push_back(tmpVector.x);
				rawVerticesData.push_back(tmpVector.y);
				rawVerticesData.push_back(tmpVector.z);

				rawVerticesData.push_back(i / static_cast<float>(divisionX));
				rawVerticesData.push_back(1.0f - j / static_cast<float>(divisionY));

				tmpVector[uIndex] = 0.0f;
				tmpVector[vIndex] = 0.0f;
				tmpVector[wIndex] = (depth > 0.0f) ? 1.0f : -1.0f;
				rawVerticesData.push_back(tmpVector.x);
				rawVerticesData.push_back(tmpVector.y);
				rawVerticesData.push_back(tmpVector.z);

				if (m_isIncludeTB)
				{
					tmpVector[uIndex] = 1.0f;
					tmpVector[vIndex] = 0.0f;
					tmpVector[wIndex] = 0.0f;
					rawVerticesData.push_back(tmpVector.x);
					rawVerticesData.push_back(tmpVector.y);
					rawVerticesData.push_back(tmpVector.z);

					tmpVector[uIndex] = 0.0f;
					tmpVector[vIndex] = 1.0f;
					tmpVector[wIndex] = 0.0f;
					rawVerticesData.push_back(tmpVector.x);
					rawVerticesData.push_back(tmpVector.y);
					rawVerticesData.push_back(tmpVector.z);
				}

				++vertexCount;
			}
		}

		for (unsigned i{ 0 }; i < divisionY; ++i)
		{
			for (unsigned j{ 0 }; j < divisionX; ++j)
			{
				const unsigned index1 = currentVertexCount + j + (divisionX + 1) * i;
				const unsigned index2 = currentVertexCount + j + (divisionX + 1) * (i + 1);
				const unsigned index3 = currentVertexCount + (j + 1) + (divisionX + 1) * (i + 1);
				const unsigned index4 = currentVertexCount + (j + 1) + (divisionX + 1) * i;

				rawIndicesData.push_back(index1);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index4);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index3);
				rawIndicesData.push_back(index4);
			}
		}

		return vertexCount;
	}

}
