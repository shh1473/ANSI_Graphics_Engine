#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class InputExecutor;
	class Geometry;
	class VertexArray;

	class InputParam
	{
	public:
		friend class InputExecutor;

		explicit InputParam();

		void SetVertexArray(VertexArray * vertexArray);
		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) { m_primitiveTopology = primitiveTopology; }

	private:
		static const PrimitiveTopology m_DefaultPrimitiveTopology;

	private:
		unsigned m_vertexArrayId;
		unsigned m_indexBufferId;
		unsigned m_vertexCount;
		unsigned m_indexCount;
		PrimitiveTopology m_primitiveTopology;

	};

}
