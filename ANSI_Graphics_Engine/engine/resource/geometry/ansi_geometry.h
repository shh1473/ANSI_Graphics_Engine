#pragma once

#include "common/ansi_common.h"

namespace AN
{

	constexpr unsigned POSITION{ 1 << 0 };
	constexpr unsigned TEXCOORD{ 1 << 1 };
	constexpr unsigned NORMAL{ 1 << 2 };

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

		bool GeneratePlane(float width, float height, unsigned widthSegments, unsigned heightSegments);
		bool GenerateBox(float width, float height, float depth, unsigned widthSegments, unsigned heightSegments, unsigned depthSegments);
		bool GenerateSphere(float radius, unsigned widthSegments, unsigned heightSegments);
		bool GenerateCylinder(float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments);
		bool GenerateFromObj(const std::string & filePath);
		
	private:
		unsigned m_vertexCount;
		unsigned m_indexCount;
		unsigned m_vertexBufferId;
		unsigned m_indexBufferId;
		std::vector<VertexArray *> m_vertexArrays;

	};

}
