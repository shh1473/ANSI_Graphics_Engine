#include "ansi_raster_executor.h"

namespace AN
{

	RasterExecutor::RasterExecutor()
	{
		m_fillMode.Set(RasterParam::m_DefaultFillMode);
		m_cullMode.Set(RasterParam::m_DefaultCullMode);
		m_frontFace.Set(RasterParam::m_DefaultFrontFace);
		m_msaa.Set(RasterParam::m_DefaultMSAA);
		m_depthClipNear.Set(RasterParam::m_DefaultDepthClipNear);
		m_depthClipFar.Set(RasterParam::m_DefaultDepthClipFar);

		m_fillMode.Reset();
		m_cullMode.Reset();
		m_frontFace.Reset();
		m_msaa.Reset();
		m_depthClipNear.Reset();
		m_depthClipFar.Reset();
	}

	bool RasterExecutor::Apply(RasterParam * param)
	{
		m_fillMode.Set(param->m_fillMode);
		m_cullMode.Set(param->m_cullMode);
		m_frontFace.Set(param->m_frontFace);
		m_msaa.Set(param->m_msaa);
		m_depthClipNear.Set(param->m_depthClipNear);
		m_depthClipFar.Set(param->m_depthClipFar);

		if (m_fillMode.Check())
		{
			m_fillMode.Reset();
			GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, static_cast<unsigned>(m_fillMode.Get())));
		}

		if (m_cullMode.Check())
		{
			m_cullMode.Reset();
			if (m_cullMode.Get() == CullMode::None)
			{
				GL_CHECK(glDisable(GL_CULL_FACE));
			}
			else
			{
				GL_CHECK(glEnable(GL_CULL_FACE));
				GL_CHECK(glCullFace(static_cast<unsigned>(m_cullMode.Get())));
			}
		}

		if (m_frontFace.Check())
		{
			m_frontFace.Reset();
			GL_CHECK(glFrontFace(static_cast<unsigned>(m_frontFace.Get())));
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

		if (m_depthClipNear.Check() || m_depthClipFar.Check())
		{
			m_depthClipNear.Reset();
			m_depthClipFar.Reset();
			GL_CHECK(glDepthRange(m_depthClipNear.Get(), m_depthClipFar.Get()));
		}

		return true;
	}

}
