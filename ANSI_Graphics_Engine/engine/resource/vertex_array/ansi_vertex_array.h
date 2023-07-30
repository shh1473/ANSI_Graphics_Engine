#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class VertexArray
	{
	public:
		explicit VertexArray(unsigned vertexArrayId, unsigned indexBufferId, unsigned vertexCount, unsigned indexCount);
		virtual ~VertexArray();

		unsigned GetVertexArrayId() const { return m_vertexArrayId; }
		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		unsigned GetVertexCount() const { return m_vertexCount; }
		unsigned GetIndexCount() const { return m_indexCount; }

	private:
		unsigned m_vertexArrayId;
		unsigned m_indexBufferId;
		unsigned m_vertexCount;
		unsigned m_indexCount;

	};

}
