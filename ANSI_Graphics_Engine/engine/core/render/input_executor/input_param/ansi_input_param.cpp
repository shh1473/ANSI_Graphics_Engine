#include "ansi_input_param.h"

#include "resource/vertex_array/ansi_vertex_array.h"

namespace AN
{

	PrimitiveTopology const InputParam::m_DefaultPrimitiveTopology{ PrimitiveTopology::Triangles };

	InputParam::InputParam() :
		m_vertexArrayId(0),
		m_indexBufferId(0),
		m_vertexCount(0),
		m_indexCount(0),
		m_primitiveTopology(m_DefaultPrimitiveTopology)
	{

	}

	void InputParam::SetGeometry(VertexArray * vertexArray)
	{
		m_vertexArrayId = vertexArray->GetVertexArrayId();
		m_indexBufferId = vertexArray->GetIndexBufferId();
		m_vertexCount = vertexArray->GetVertexCount();
		m_indexCount = vertexArray->GetIndexCount();
	}

}
