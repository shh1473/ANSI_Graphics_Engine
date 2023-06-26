#pragma once

#include "common/ansi_common.h"

namespace AN
{

	enum class PrimitiveTopology
	{
		Points = GL_POINTS,
		Lines = GL_LINES,
		LineLoop = GL_LINE_LOOP,
		LineStrip = GL_LINE_STRIP,
		Triangles = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN,
		Patches = GL_PATCHES,
	};

	class InputExecutor;

	class InputParam
	{
	public:
		friend class InputExecutor;

		explicit InputParam();

		void SetVertexArrayId(unsigned vertexArrayId) { m_vertexArrayId = vertexArrayId; }
		void SetIndexBufferId(unsigned indexBufferId) { m_indexBufferId = indexBufferId; }
		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) { m_primitiveTopology = primitiveTopology; }

	private:
		static const unsigned m_DefaultVertexArrayId;
		static const unsigned m_DefaultIndexBufferId;
		static const PrimitiveTopology m_DefaultPrimitiveTopology;

		unsigned m_vertexArrayId;
		unsigned m_indexBufferId;
		PrimitiveTopology m_primitiveTopology;

	};

}
