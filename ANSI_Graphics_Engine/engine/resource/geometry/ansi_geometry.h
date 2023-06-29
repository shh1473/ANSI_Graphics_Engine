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
		void RemoveVertexArray(VertexArray * vertexArray);

		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		unsigned GetVertexCount() const { return m_vertexCount; }
		unsigned GetIndexCount() const { return m_indexCount; }

		bool GenerateBox(float width, float height, float depth, unsigned widthDivision, unsigned heightDivision, unsigned depthDivision, bool isIncludeTB);
		bool GenerateFromObj(const std::string & filePath, bool isIncludeTB);
		
	private:
		unsigned m_vertexCount;
		unsigned m_indexCount;
		unsigned m_vertexBufferId;
		unsigned m_indexBufferId;
		std::vector<VertexArray *> m_vertexArrays;

	};

}
