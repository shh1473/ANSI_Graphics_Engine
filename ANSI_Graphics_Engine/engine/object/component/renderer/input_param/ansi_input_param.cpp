#include "ansi_input_param.h"

namespace AN
{

	unsigned const InputParam::m_DefaultVertexArrayId{ 0 };
	unsigned const InputParam::m_DefaultIndexBufferId{ 0 };
	PrimitiveTopology const InputParam::m_DefaultPrimitiveTopology{ PrimitiveTopology::Triangles };

	InputParam::InputParam() :
		m_isEnableDepthTest(true),
		m_isEnableDepthWrite(true),
		m_vertexArrayId(m_DefaultVertexArrayId),
		m_indexBufferId(m_DefaultIndexBufferId),
		m_vertexCount(0),
		m_indexCount(0),
		m_primitiveTopology(m_DefaultPrimitiveTopology)
	{

	}

}
