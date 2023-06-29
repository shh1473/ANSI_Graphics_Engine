// >========================================================================================<
//  본 ansi_box_geometry_generator.cpp 파일의 내용은 Three.js의 BoxGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/BoxGeometry.js
// >========================================================================================<

#include "ansi_box_geometry_generator.h"

namespace AN
{

	bool BoxGeometryGenerator::Create(
		float width, float height, float depth,
		unsigned widthDivision, unsigned heightDivision, unsigned depthDivision, bool isIncludeTB,
		unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount)
	{
		unsigned currentVertexCount{ 0 };
		std::vector<float> rawVerticesData;
		std::vector<unsigned> rawIndicesData;
		rawVerticesData.reserve((
			(widthDivision + 1) * (heightDivision + 1) + (widthDivision + 1) * (heightDivision + 1) +
			(widthDivision + 1) * (depthDivision + 1) + (widthDivision + 1) * (depthDivision + 1) +
			(depthDivision + 1) * (heightDivision + 1) + (depthDivision + 1) * (heightDivision + 1)) * (isIncludeTB ? 14 : 8));
		rawIndicesData.reserve((
			widthDivision * heightDivision + widthDivision * heightDivision +
			widthDivision * depthDivision + widthDivision * depthDivision +
			depthDivision * heightDivision + depthDivision * heightDivision) * 6);

		currentVertexCount += BuildPlane(0, 1, 2, 1, -1, width, height, depth, widthDivision, heightDivision, isIncludeTB, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 1, 2, -1, -1, width, height, -depth, widthDivision, heightDivision, isIncludeTB, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 2, 1, 1, 1, width, depth, height, widthDivision, depthDivision, isIncludeTB, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 2, 1, 1, -1, width, depth, -height, widthDivision, depthDivision, isIncludeTB, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(2, 1, 0, -1, -1, depth, height, width, depthDivision, heightDivision, isIncludeTB, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(2, 1, 0, 1, -1, depth, height, -width, depthDivision, heightDivision, isIncludeTB, currentVertexCount, rawVerticesData, rawIndicesData);

		vertexCount = static_cast<unsigned>(rawVerticesData.size());
		indexCount = static_cast<unsigned>(rawIndicesData.size());

		GL_CHECK(glGenBuffers(1, &vertexBufferId));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), rawVerticesData.data(), GL_STATIC_DRAW));

		GL_CHECK(glGenBuffers(1, &indexBufferId));
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndicesData.size() * sizeof(unsigned), rawIndicesData.data(), GL_STATIC_DRAW));

		return true;
	}

	unsigned BoxGeometryGenerator::BuildPlane(
		unsigned uIndex, unsigned vIndex, unsigned wIndex, float uDirection, float vDirection,
		float width, float height, float depth, unsigned divisionX, unsigned divisionY, bool isIncludeTB,
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
				tmpVector[uIndex] = (j * segmentWidth - halfWidth) * uDirection;
				tmpVector[vIndex] = (i * segmentHeight - halfHeight) * vDirection;
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

				if (isIncludeTB)
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
