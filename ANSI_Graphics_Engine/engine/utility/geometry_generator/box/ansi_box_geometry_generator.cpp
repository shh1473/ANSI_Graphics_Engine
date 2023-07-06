// >========================================================================================<
//  �� ansi_box_geometry_generator.cpp ������ ������ Three.js�� BoxGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/BoxGeometry.js
// >========================================================================================<

#include "ansi_box_geometry_generator.h"

namespace AN
{

	bool BoxGeometryGenerator::Create(
		bool isIncludeTB, float width, float height, float depth,
		unsigned widthSegments, unsigned heightSegments, unsigned depthSegments,
		unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount)
	{
		vertexCount = (
			(widthSegments + 1) * (heightSegments + 1) + (widthSegments + 1) * (heightSegments + 1) +
			(widthSegments + 1) * (depthSegments + 1) + (widthSegments + 1) * (depthSegments + 1) +
			(depthSegments + 1) * (heightSegments + 1) + (depthSegments + 1) * (heightSegments + 1)) * (isIncludeTB ? 14 : 8);
		indexCount = (
			widthSegments * heightSegments + widthSegments * heightSegments +
			widthSegments * depthSegments + widthSegments * depthSegments +
			depthSegments * heightSegments + depthSegments * heightSegments) * 6;

		unsigned currentVertexCount{ 0 };
		std::vector<float> rawVerticesData;
		std::vector<unsigned> rawIndicesData;
		rawVerticesData.reserve(vertexCount);
		rawIndicesData.reserve(indexCount);

		currentVertexCount += BuildPlane(isIncludeTB, 0, 1, 2, 1, -1, width, height, depth, widthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(isIncludeTB, 0, 1, 2, -1, -1, width, height, -depth, widthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(isIncludeTB, 0, 2, 1, 1, 1, width, depth, height, widthSegments, depthSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(isIncludeTB, 0, 2, 1, 1, -1, width, depth, -height, widthSegments, depthSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(isIncludeTB, 2, 1, 0, -1, -1, depth, height, width, depthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(isIncludeTB, 2, 1, 0, 1, -1, depth, height, -width, depthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);

		GL_CHECK(glGenBuffers(1, &vertexBufferId));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), rawVerticesData.data(), GL_STATIC_DRAW));

		GL_CHECK(glGenBuffers(1, &indexBufferId));
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndicesData.size() * sizeof(unsigned), rawIndicesData.data(), GL_STATIC_DRAW));

		return true;
	}

	unsigned BoxGeometryGenerator::BuildPlane(
		bool isIncludeTB, unsigned uIndex, unsigned vIndex, unsigned wIndex, float uDirection, float vDirection,
		float width, float height, float depth, unsigned divisionX, unsigned divisionY, unsigned currentVertexCount,
		std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData)
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

		unsigned index1{ 0 };
		unsigned index2{ 0 };
		unsigned index3{ 0 };
		unsigned index4{ 0 };

		for (unsigned i{ 0 }; i < divisionY; ++i)
		{
			for (unsigned j{ 0 }; j < divisionX; ++j)
			{
				index1 = currentVertexCount + j + (divisionX + 1) * i;
				index2 = currentVertexCount + j + (divisionX + 1) * (i + 1);
				index3 = currentVertexCount + (j + 1) + (divisionX + 1) * (i + 1);
				index4 = currentVertexCount + (j + 1) + (divisionX + 1) * i;

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