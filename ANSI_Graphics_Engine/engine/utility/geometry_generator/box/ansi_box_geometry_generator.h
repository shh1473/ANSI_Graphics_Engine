// >========================================================================================<
//  �� ansi_box_geometry_generator.h ������ ������ Three.js�� BoxGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
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
