#include "ansi_depth_spot_camera.h"

#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/texture/ansi_texture.h"

namespace AN
{

	DepthSpotCamera::DepthSpotCamera(Object * object) :
		Camera(object, CameraType::Light_Spot, false),
		m_depthMap(nullptr)
	{

	}

	DepthSpotCamera::~DepthSpotCamera()
	{
		AN_DELETE(m_depthMap);
	}

	bool DepthSpotCamera::CreateDepthMap()
	{
		unsigned depthMapId{ 0 };
		GL_CHECK(glGenTextures(1, &depthMapId));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMapId));
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24,
			static_cast<int>(m_width.Get()), static_cast<int>(m_height.Get()), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));

		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

		m_depthMap = new Texture(depthMapId, static_cast<unsigned>(m_width.Get()), static_cast<unsigned>(m_height.Get()));

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer->GetId()));

		GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap->GetId(), 0));
		AN_CHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		GL_CHECK(glDrawBuffer(GL_NONE));
		GL_CHECK(glReadBuffer(GL_NONE));

		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		return true;
	}

}
