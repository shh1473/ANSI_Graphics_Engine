// >========================================================================================<
//  본 ansi_cylinder_geometry_generator.h 파일의 내용은 Three.js의 CylinderGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/CylinderGeometry.js
// >========================================================================================<

#include "ansi_cylinder_geometry_generator.h"

namespace AN
{

	bool CylinderGeometryGenerator::Create(
		bool isIncludeTB, bool isOpenEnded, float topRadius, float bottomRadius, float height, float thetaStart, float thetaLength,
		unsigned radialSegments, unsigned heightSegments, unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount)
	{
		vertexCount = (radialSegments * (heightSegments + 1) + ((isOpenEnded) ? 0 : 2)) * (isIncludeTB ? 14 : 8);
		indexCount = ((radialSegments * heightSegments * 2) + ((isOpenEnded) ? 0 : (radialSegments * 2))) * 3;

		unsigned currentIndex{ 0 };
		std::vector<float> rawVerticesData;
		std::vector<unsigned> rawIndicesData;
		rawVerticesData.reserve(vertexCount);
		rawIndicesData.reserve(indexCount);

		GenerateTorso(topRadius, bottomRadius, height, thetaStart, thetaLength, radialSegments, heightSegments, currentIndex, rawVerticesData, rawIndicesData);

		if (!isOpenEnded)
		{
			if (topRadius > 0.0f) { GenerateCap(true, topRadius, bottomRadius, height, thetaStart, thetaLength, radialSegments, currentIndex, rawVerticesData, rawIndicesData); }
			if (bottomRadius > 0.0f) { GenerateCap(false, topRadius, bottomRadius, height, thetaStart, thetaLength, radialSegments, currentIndex, rawVerticesData, rawIndicesData); }
		}

		GL_CHECK(glGenBuffers(1, &vertexBufferId));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), rawVerticesData.data(), GL_STATIC_DRAW));

		GL_CHECK(glGenBuffers(1, &indexBufferId));
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndicesData.size() * sizeof(unsigned), rawIndicesData.data(), GL_STATIC_DRAW));

		return true;
	}

	void CylinderGeometryGenerator::GenerateTorso(
		float topRadius, float bottomRadius, float height, float thetaStart, float thetaLength, unsigned radialSegments, unsigned heightSegments,
		unsigned & currentIndex, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData)
	{
		const float slope = (bottomRadius - topRadius) / height;
		const float halfHeight{ height * 0.5f };
		float u{ 0.0f }, v{ 0.0f };
		float theta{ 0.0f }, sinTheta{ 0.0f }, cosTheta{ 0.0f }, radius{ 0.0f };
		std::vector<unsigned> indexRow;
		std::vector<std::vector<unsigned>> indexArray;

		for (unsigned i{ 0 }; i <= heightSegments; ++i)
		{
			v = i / static_cast<float>(heightSegments);
			radius = v * (bottomRadius - topRadius) + topRadius;

			for (unsigned j{ 0 }; j <= radialSegments; ++j)
			{
				u = j / static_cast<float>(radialSegments);
				theta = (u * thetaLength) + thetaStart;
				sinTheta = std::sin(theta);
				cosTheta = std::cos(theta);

				rawVerticesData.push_back(radius * sinTheta);
				rawVerticesData.push_back((height * -v) + halfHeight);
				rawVerticesData.push_back(radius * cosTheta);

				rawVerticesData.push_back(u);
				rawVerticesData.push_back(1.0f - v);

				rawVerticesData.push_back(sinTheta);
				rawVerticesData.push_back(slope);
				rawVerticesData.push_back(cosTheta);

				indexRow.push_back(currentIndex++);
			}

			indexArray.push_back(indexRow);
			indexRow.clear();
		}

		unsigned index1{ 0 };
		unsigned index2{ 0 };
		unsigned index3{ 0 };
		unsigned index4{ 0 };

		for (unsigned i{ 0 }; i < heightSegments; ++i)
		{
			for (unsigned j{ 0 }; j < radialSegments; ++j)
			{
				index1 = indexArray[i][j];
				index2 = indexArray[static_cast<std::size_t>(i) + 1][j];
				index3 = indexArray[static_cast<std::size_t>(i) + 1][static_cast<std::size_t>(j) + 1];
				index4 = indexArray[i][static_cast<std::size_t>(j) + 1];

				rawIndicesData.push_back(index1);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index4);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index3);
				rawIndicesData.push_back(index4);
			}
		}
	}

	void CylinderGeometryGenerator::GenerateCap(
		bool isTop, float topRadius, float bottomRadius, float height, float thetaStart, float thetaLength, unsigned radialSegments,
		unsigned & currentIndex, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData)
	{
		const unsigned centerIndexStart{ currentIndex };
		const float radius{ isTop ? topRadius : bottomRadius };
		const float sign{ isTop ? 1.0f : -1.0f };
		const float halfHeight{ height * 0.5f };

		for (unsigned i{ 1 }; i <= radialSegments; ++i)
		{
			rawVerticesData.push_back(0.0f);
			rawVerticesData.push_back(sign * halfHeight);
			rawVerticesData.push_back(0.0f);

			rawVerticesData.push_back(0.5f);
			rawVerticesData.push_back(0.5f);

			rawVerticesData.push_back(0.0f);
			rawVerticesData.push_back(sign);
			rawVerticesData.push_back(0.0f);

			currentIndex++;
		}

		const unsigned centerIndexEnd{ currentIndex };

		for (unsigned i{ 0 }; i <= radialSegments; ++i)
		{
			const float u{ i / static_cast<float>(radialSegments) };
			const float theta{ u * thetaLength + thetaStart };
			const float cosTheta{ std::cos(theta) };
			const float sinTheta{ std::sin(theta) };

			rawVerticesData.push_back(radius * sinTheta);
			rawVerticesData.push_back(halfHeight * sign);
			rawVerticesData.push_back(radius * cosTheta);

			rawVerticesData.push_back((cosTheta * 0.5f) + 0.5f);
			rawVerticesData.push_back((sinTheta * 0.5f * sign) + 0.5f);

			rawVerticesData.push_back(0.0f);
			rawVerticesData.push_back(sign);
			rawVerticesData.push_back(0.0f);

			currentIndex++;
		}

		unsigned start{ 0 };
		unsigned end{ 0 };

		for (unsigned i{ 0 }; i < radialSegments; ++i)
		{
			start = centerIndexStart + i;
			end = centerIndexEnd + i;

			if (isTop) {
				rawIndicesData.push_back(end);
				rawIndicesData.push_back(end + 1);
				rawIndicesData.push_back(start);
			}
			else
			{
				rawIndicesData.push_back(end + 1);
				rawIndicesData.push_back(end);
				rawIndicesData.push_back(start);
			}
		}
	}

}
