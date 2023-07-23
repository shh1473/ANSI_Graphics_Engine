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

		void SetVertices(unsigned id, unsigned count) { m_vertexArrayId = id; m_vertexCount = count; }
		void SetIndices(unsigned id, unsigned count) { m_indexBufferId = id; m_indexCount = count; }
		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) { m_primitiveTopology = primitiveTopology; }

	private:
		static const PrimitiveTopology m_DefaultPrimitiveTopology;

		bool m_isEnableDepthTest;
		bool m_isEnableDepthWrite;
		unsigned m_vertexArrayId;
		unsigned m_indexBufferId;
		unsigned m_vertexCount;
		unsigned m_indexCount;
		PrimitiveTopology m_primitiveTopology;

	};

}
