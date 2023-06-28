#pragma once

#include "common/ansi_common.h"

namespace AN
{

	constexpr unsigned POSITION{ 1 << 0 };
	constexpr unsigned TEXCOORD{ 1 << 1 };
	constexpr unsigned NORMAL{ 1 << 2 };
	constexpr unsigned TANGENTBINORMAL{ 1 << 3 };

	struct VertexElement
	{
		unsigned char normalized;
		unsigned count;
		unsigned type;
	};

	class VertexArray;

	class Geometry
	{
	public:
		explicit Geometry();
		virtual ~Geometry();

		VertexArray * GenerateVertexArray(unsigned flag = POSITION | TEXCOORD | NORMAL);

		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		unsigned GetVertexCount() const { return m_vertexCount; }
		unsigned GetIndexCount() const { return m_indexCount; }

		bool CreateCube(float width, float height, float depth, unsigned widthDivision, unsigned heightDivision, unsigned depthDivision, bool isCalculateTB);
		bool LoadFromObj(const std::string & filePath, bool isIncludeTB);
		
	private:
		unsigned BuildPlane(
			unsigned uIndex, unsigned vIndex, unsigned wIndex, float uDirection, float vDirection,
			float width, float height, float depth, unsigned divisionX, unsigned divisionY,
			unsigned currentVertexCount, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

		bool m_isIncludeTB;
		unsigned m_vertexCount;
		unsigned m_indexCount;
		unsigned m_vertexBufferId;
		unsigned m_indexBufferId;
		std::vector<VertexArray *> m_vertexArrays;

	};

}
