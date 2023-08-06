#include "ansi_depth_point_camera.h"

#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/texture/ansi_texture.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace AN
{

	DepthPointCamera::DepthPointCamera(Object * object) :
		Camera(object, CameraType::Light_Point, false),
		m_depthMap(nullptr),
		m_viewProjMatrices{ glm::mat4(1.0f), }
	{
		m_isUpdateViewMatrix = false;
	}

	DepthPointCamera::~DepthPointCamera()
	{
		AN_DELETE(m_depthMap);
	}

	bool DepthPointCamera::OnUpdate()
	{
		static glm::vec3 worldPosition(0.0f);
		worldPosition = GetObject()->GetTransform()->GetWorldPosition();

		AN_CHECK(Camera::OnUpdate());

		if (!GetObject()->GetTransform()->GetIsChangedMatrix()) { return true; }

		m_viewProjMatrices[0] = glm::lookAt(worldPosition, worldPosition + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
		m_viewProjMatrices[1] = glm::lookAt(worldPosition, worldPosition + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
		m_viewProjMatrices[2] = glm::lookAt(worldPosition, worldPosition + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
		m_viewProjMatrices[3] = glm::lookAt(worldPosition, worldPosition + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
		m_viewProjMatrices[4] = glm::lookAt(worldPosition, worldPosition + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
		m_viewProjMatrices[5] = glm::lookAt(worldPosition, worldPosition + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0));

		for (unsigned i{ 0 }; i < 6; ++i)
		{
			m_viewProjMatrices[i] = m_projMatrix * m_viewProjMatrices[i];
		}

		return true;
	}

	bool DepthPointCamera::CreateDepthMap()
	{
		unsigned depthMapId{ 0 };
		GL_CHECK(glGenTextures(1, &depthMapId));
		GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, depthMapId));

		for (unsigned i{ 0 }; i < 6; ++i)
		{
			GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT24,
				static_cast<int>(m_width.Get()), static_cast<int>(m_height.Get()), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
		}

		GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
		GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
		GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER));

		m_depthMap = new Texture(depthMapId, static_cast<unsigned>(m_width.Get()), static_cast<unsigned>(m_height.Get()));

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer->GetId()));

		GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthMap->GetId(), 0));
		AN_CHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		GL_CHECK(glDrawBuffer(GL_NONE));
		GL_CHECK(glReadBuffer(GL_NONE));

		GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		return true;
	}

}
