#include "ansi_vertex_array.h"

namespace AN
{

	VertexArray::VertexArray(unsigned id) :
		m_id(id)
	{

	}

	VertexArray::~VertexArray()
	{
		GL_ERROR_LOG(glBindVertexArray(0));
		GL_ERROR_LOG(glDeleteVertexArrays(1, &m_id));
	}

}
