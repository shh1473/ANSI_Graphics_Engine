#include "ansi_input_param.h"

namespace AN
{

	PrimitiveTopology const InputParam::m_DefaultPrimitiveTopology{ PrimitiveTopology::Triangles };

	InputParam::InputParam() :
		m_isEnableDepthTest(true),
		m_isEnableDepthWrite(true),
		m_vertexArrayId(0),
		m_indexBufferId(0),
		m_vertexCount(0),
		m_indexCount(0),
		m_primitiveTopology(m_DefaultPrimitiveTopology)
	{

	}

}
