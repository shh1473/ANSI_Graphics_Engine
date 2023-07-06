#include "ansi_input_executor.h"

namespace AN
{

	InputExecutor::InputExecutor() :
		m_vertexCount(0),
		m_indexCount(0),
		m_dispatchSize(1),
		m_primitiveTopology(InputParam::m_DefaultPrimitiveTopology)
	{
		m_vertexArrayId.Set(InputParam::m_DefaultVertexArrayId);
		m_indexBufferId.Set(InputParam::m_DefaultIndexBufferId);
	}

	bool InputExecutor::Apply(InputParam * param)
	{
		m_vertexArrayId.Set(param->m_vertexArrayId);
		m_indexBufferId.Set(param->m_indexBufferId);
		m_vertexCount = param->m_vertexCount;
		m_indexCount = param->m_indexCount;
		m_primitiveTopology = param->m_primitiveTopology;

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

	bool InputExecutor::Apply(DispatchParam * param)
	{
		m_dispatchSize = param->m_size;

		return true;
	}

}
