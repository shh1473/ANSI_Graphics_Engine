#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class VertexArray;

	class Geometry
	{
	public:
		explicit Geometry();
		virtual ~Geometry();

		VertexArray * GenerateVertexArray(unsigned flag = TEXCOORD | NORMAL);
		void RemoveVertexArray(VertexArray * vertexArray);

		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		unsigned GetVertexCount() const { return m_vertexCount; }
		unsigned GetIndexCount() const { return m_indexCount; }

		bool GeneratePlane(float width, float height, unsigned widthSegments = 1, unsigned heightSegments = 1);
		bool GenerateBox(float width, float height, float depth, unsigned widthSegments = 1, unsigned heightSegments = 1, unsigned depthSegments = 1);
		bool GenerateSphere(float radius, unsigned widthSegments = 16, unsigned heightSegments = 8);
		bool GenerateCylinder(float topRadius, float bottomRadius, float height, unsigned radialSegments = 16, unsigned heightSegments = 1);
		bool GenerateFromObj(const std::string & filePath);
		
	private:
		unsigned m_vertexCount;
		unsigned m_indexCount;
		unsigned m_vertexBufferId;
		unsigned m_indexBufferId;
		unsigned m_stride;
		unsigned m_flag;
		std::vector<VertexArray *> m_vertexArrays;

	};

}
