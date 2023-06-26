#include "ansi_input_executor.h"

namespace AN
{

	InputExecutor::InputExecutor() :
		m_primitiveTopology(InputParam::m_DefaultPrimitiveTopology)
	{
		m_vertexArrayId.Set(InputParam::m_DefaultVertexArrayId);
		m_indexBufferId.Set(InputParam::m_DefaultIndexBufferId);

		m_vertexArrayId.Reset();
		m_indexBufferId.Reset();
	}

	bool InputExecutor::Apply(InputParam * param)
	{
		m_vertexArrayId.Set(param->m_vertexArrayId);
		m_indexBufferId.Set(param->m_indexBufferId);

		if (m_vertexArrayId.Check())
		{
			m_vertexArrayId.Reset();
			GL_CHECK(glBindVertexArray(m_vertexArrayId.Get()));
		}

		if (m_indexBufferId.Check())
		{
			m_indexBufferId.Reset();
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId.Get()));
		}

		return true;
	}

}
