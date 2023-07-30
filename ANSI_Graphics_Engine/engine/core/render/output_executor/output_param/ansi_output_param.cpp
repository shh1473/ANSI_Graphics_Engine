#include "ansi_output_param.h"

namespace AN
{

	const int OutputParam::m_DefaultClearStencil{ 0 };
	const float OutputParam::m_DefaultClearDepth{ 1.0f };
	const glm::vec4 OutputParam::m_DefaultClearColor{ 0.0f, 0.0f, 0.0f, 1.0f };
	const MSAA OutputParam::m_DefaultMsaa{ MSAA::None };

	OutputParam::OutputParam() :
		m_clearStencil(m_DefaultClearStencil),
		m_clearDepth(m_DefaultClearDepth),
		m_clearColor(m_DefaultClearColor),
		m_msaa(m_DefaultMsaa),
		m_frameBufferId(0)
	{

	}

}
