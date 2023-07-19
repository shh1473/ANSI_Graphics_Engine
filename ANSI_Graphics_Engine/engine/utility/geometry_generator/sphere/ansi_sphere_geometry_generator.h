// >========================================================================================<
//  본 ansi_sphere_geometry_generator.h 파일의 내용은 Three.js의 SphereGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/SphereGeometry.js
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class SphereGeometryGenerator
	{
	public:
		static bool Generate(
			float radius, unsigned widthSegments, unsigned heightSegments, unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit SphereGeometryGenerator() = delete;

		static void GenerateSphere(float radius, unsigned widthSegments, unsigned heightSegments, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
