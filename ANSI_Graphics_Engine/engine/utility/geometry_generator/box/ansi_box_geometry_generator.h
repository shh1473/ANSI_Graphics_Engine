// >========================================================================================<
//  본 ansi_box_geometry_generator.h 파일의 내용은 Three.js의 BoxGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/BoxGeometry.js
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class BoxGeometryGenerator
	{
	public:
		static bool Create(
			float width, float height, float depth,
			unsigned widthDivision, unsigned heightDivision, unsigned depthDivision, bool isCalculateTB,
			unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit BoxGeometryGenerator() = delete;

		static unsigned BuildPlane(
			unsigned uIndex, unsigned vIndex, unsigned wIndex, float uDirection, float vDirection,
			float width, float height, float depth, unsigned divisionX, unsigned divisionY, bool isIncludeTB,
			unsigned currentVertexCount, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
