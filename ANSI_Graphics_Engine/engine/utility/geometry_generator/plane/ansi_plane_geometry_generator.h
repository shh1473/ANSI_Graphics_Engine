// >========================================================================================<
//  본 ansi_plane_geometry_generator.cpp 파일의 내용은 Three.js의 PlaneGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/PlaneGeometry.js
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class PlaneGeometryGenerator
	{
	public:
		static bool Generate(
			float width, float height, unsigned widthSegments, unsigned heightSegments,
			unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit PlaneGeometryGenerator() = delete;

		static void BuildPlane(
			float width, float height, unsigned divisionX, unsigned divisionY,
			std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
