#include "ansi_vertex_array.h"

namespace AN
{

	VertexArray::VertexArray(unsigned vertexArrayId, unsigned indexBufferId, unsigned vertexCount, unsigned indexCount) :
		m_vertexArrayId(vertexArrayId),
		m_indexBufferId(indexBufferId),
		m_vertexCount(vertexCount),
		m_indexCount(indexCount)
	{

	}

	VertexArray::~VertexArray()
	{
		GL_ERROR_LOG(glDeleteVertexArrays(1, &m_vertexArrayId));
	}

}
