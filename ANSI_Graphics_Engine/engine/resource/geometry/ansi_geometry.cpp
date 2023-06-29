#include "ansi_geometry.h"

#include "core/log/ansi_log.h"
#include "resource/vertex_array/ansi_vertex_array.h"
#include "utility/geometry_generator/box/ansi_box_geometry_generator.h"
#include "utility/obj_loader/ansi_obj_loader.h"

namespace AN
{

	Geometry::Geometry() :
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
		AN_CHECK_NULL(m_vertexCount != 0);

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

	void Geometry::RemoveVertexArray(VertexArray * vertexArray)
	{
		m_vertexArrays.erase(std::find(m_vertexArrays.begin(), m_vertexArrays.end(), vertexArray));
		AN_DELETE(vertexArray);
	}

	bool Geometry::GenerateBox(float width, float height, float depth, unsigned widthDivision, unsigned heightDivision, unsigned depthDivision, bool isIncludeTB)
	{
		AN_CHECK_LOG(m_vertexCount == 0);
		return BoxGeometryGenerator::Create(
			width, height, depth, widthDivision, heightDivision, depthDivision, isIncludeTB,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	bool Geometry::GenerateFromObj(const std::string & filePath, bool isIncludeTB)
	{
		AN_CHECK_LOG(m_vertexCount == 0);
		return ObjLoader::LoadObj(filePath, isIncludeTB, m_vertexBufferId, m_vertexCount);
	}

}
