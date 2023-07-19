// >========================================================================================<
//  본 ansi_cylinder_geometry_generator.h 파일의 내용은 Three.js의 CylinderGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/CylinderGeometry.js
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class CylinderGeometryGenerator
	{
	public:
		static bool Create(
			float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments,
			unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit CylinderGeometryGenerator() = delete;

		static void GenerateTorso(float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments,
			unsigned & currentIndex, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);
		static void GenerateCap(bool isTop, float topRadius, float bottomRadius, float height, unsigned radialSegments,
			unsigned & currentIndex, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
