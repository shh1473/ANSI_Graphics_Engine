#include "ansi_output_executor.h"

namespace AN
{

	OutputExecutor::OutputExecutor()
	{
		m_isEnableBlend.Set(OutputParam::m_DefaultIsEnableBlend);
		m_frameBufferId.Set(OutputParam::m_DefaultFrameBufferId);
		m_srcFactor.Set(OutputParam::m_DefaultSrcFactor);
		m_dstFactor.Set(OutputParam::m_DefaultDstFactor);
		m_srcAlphaFactor.Set(OutputParam::m_DefaultSrcAlphaFactor);
		m_dstAlphaFactor.Set(OutputParam::m_DefaultDstAlphaFactor);
		m_colorOp.Set(OutputParam::m_DefaultColorOp);
		m_alphaOp.Set(OutputParam::m_DefaultAlphaOp);

		m_isEnableBlend.Reset();
		m_frameBufferId.Reset();
		m_srcFactor.Reset();
		m_dstFactor.Reset();
		m_srcAlphaFactor.Reset();
		m_dstAlphaFactor.Reset();
		m_colorOp.Reset();
		m_alphaOp.Reset();
	}

	bool OutputExecutor::Apply(OutputParam * param)
	{
		m_isEnableBlend.Set(param->m_isEnableBlend);
		m_frameBufferId.Set(param->m_frameBufferId);
		m_srcFactor.Set(param->m_srcFactor);
		m_dstFactor.Set(param->m_dstFactor);
		m_srcAlphaFactor.Set(param->m_srcAlphaFactor);
		m_dstAlphaFactor.Set(param->m_dstAlphaFactor);
		m_colorOp.Set(param->m_colorOp);
		m_alphaOp.Set(param->m_alphaOp);

		if (m_frameBufferId.Check())
		{
			m_frameBufferId.Reset();
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId.Get()));
		}

		if (m_isEnableBlend.Check())
		{
			m_isEnableBlend.Reset();
			if (m_isEnableBlend.Get())
			{
				GL_CHECK(glEnable(GL_BLEND));
			}
			else
			{
				GL_CHECK(glDisable(GL_BLEND));
			}
		}

		if (m_srcFactor.Check() || m_dstFactor.Check() || m_srcAlphaFactor.Check() || m_dstAlphaFactor.Check())
		{
			m_srcFactor.Reset();
			m_dstFactor.Reset();
			m_srcAlphaFactor.Reset();
			m_dstAlphaFactor.Reset();
			GL_CHECK(glBlendFuncSeparate(
				static_cast<unsigned>(m_srcFactor.Get()),
				static_cast<unsigned>(m_dstFactor.Get()),
				static_cast<unsigned>(m_srcAlphaFactor.Get()),
				static_cast<unsigned>(m_dstAlphaFactor.Get())));
		}

		if (m_colorOp.Check() || m_alphaOp.Check())
		{
			m_colorOp.Reset();
			m_alphaOp.Reset();
			GL_CHECK(glBlendEquationSeparate(
				static_cast<unsigned>(m_colorOp.Get()),
				static_cast<unsigned>(m_alphaOp.Get())));
		}

		return true;
	}

}
