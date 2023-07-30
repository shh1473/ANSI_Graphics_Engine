#include "ansi_output_executor.h"

namespace AN
{

	OutputExecutor::OutputExecutor()
	{
		Reset();
	}

	bool OutputExecutor::Apply(OutputParam * param)
	{
		m_clearStencil.Set(param->m_clearStencil);
		m_clearDepth.Set(param->m_clearDepth);
		m_clearColor.Set(param->m_clearColor);
		m_msaa.Set(param->m_msaa);
		m_frameBufferId.Set(param->m_frameBufferId);

		if (m_clearStencil.Check())
		{
			m_clearStencil.Reset();
			GL_CHECK(glClearStencil(m_clearStencil.Get()));
		}

		if (m_clearDepth.Check())
		{
			m_clearDepth.Reset();
			GL_CHECK(glClearDepthf(m_clearDepth.Get()));
		}

		if (m_clearColor.Check())
		{
			m_clearColor.Reset();
			GL_CHECK(glClearColor(m_clearColor.Get().r, m_clearColor.Get().g, m_clearColor.Get().b, m_clearColor.Get().a));
		}

		if (m_msaa.Check())
		{
			m_msaa.Reset();
			if (m_msaa.Get() == MSAA::None)
			{
				GL_CHECK(glDisable(GL_MULTISAMPLE));
			}
			else
			{
				GL_CHECK(glEnable(GL_MULTISAMPLE));
				GL_CHECK(glHint(GL_MULTISAMPLE_FILTER_HINT_NV, static_cast<unsigned>(m_msaa.Get())));
			}
		}

		if (m_frameBufferId.Check())
		{
			m_frameBufferId.Reset();
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId.Get()));
		}

		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		return true;
	}

	void OutputExecutor::Reset()
	{
		m_clearStencil.Set(OutputParam::m_DefaultClearStencil);
		m_clearDepth.Set(OutputParam::m_DefaultClearDepth);
		m_clearColor.Set(OutputParam::m_DefaultClearColor);
		m_msaa.Set(MSAA::None);
		m_frameBufferId.Set(0);

		m_clearStencil.Reset();
		m_clearDepth.Reset();
		m_clearColor.Reset();
		m_msaa.Reset();
		m_frameBufferId.Reset();
	}

}
