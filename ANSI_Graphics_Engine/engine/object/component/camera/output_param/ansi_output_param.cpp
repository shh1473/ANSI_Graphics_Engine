#include "ansi_output_param.h"

namespace AN
{

	bool const OutputParam::m_DefaultIsEnableBlend{ false };
	unsigned const OutputParam::m_DefaultFrameBufferId{ 0 };
	BlendFactor const OutputParam::m_DefaultSrcFactor{ BlendFactor::One };
	BlendFactor const OutputParam::m_DefaultDstFactor{ BlendFactor::Zero };
	BlendFactor const OutputParam::m_DefaultSrcAlphaFactor{ BlendFactor::One };
	BlendFactor const OutputParam::m_DefaultDstAlphaFactor{ BlendFactor::Zero };
	BlendOp const OutputParam::m_DefaultColorOp{ BlendOp::Add };
	BlendOp const OutputParam::m_DefaultAlphaOp{ BlendOp::Add };

	OutputParam::OutputParam() :
		m_isEnableBlend(m_DefaultIsEnableBlend),
		m_frameBufferId(m_DefaultFrameBufferId),
		m_srcFactor(m_DefaultSrcFactor),
		m_dstFactor(m_DefaultDstFactor),
		m_srcAlphaFactor(m_DefaultSrcAlphaFactor),
		m_dstAlphaFactor(m_DefaultDstAlphaFactor),
		m_colorOp(m_DefaultColorOp),
		m_alphaOp(m_DefaultAlphaOp)
	{

	}

	OutputParam::~OutputParam()
	{

	}

}
