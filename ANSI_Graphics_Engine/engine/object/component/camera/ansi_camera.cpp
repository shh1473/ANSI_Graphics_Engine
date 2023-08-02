#include "ansi_camera.h"

#include "core/log/ansi_log.h"
#include "core/window/ansi_window.h"
#include "core/render/ansi_render.h"
#include "core/render/built_in/g_buffer_output/ansi_g_buffer_output.h"
#include "core/render/output_executor/output_param/ansi_output_param.h"
#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/texture/ansi_texture.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"
#include "utility/orbit_controls/ansi_orbit_controls.h"

namespace AN
{

	const bool Camera::m_DefaultIsPerspective{ true };
	const float Camera::m_DefaultZoom{ 1.0f };
	const float Camera::m_DefaultFov{ PI * 0.25f };
	const float Camera::m_DefaultNear{ 1.0f };
	const float Camera::m_DefaultFar{ 1000.0f };
	const float Camera::m_DefaultWidth{ 1024.0f };
	const float Camera::m_DefaultHeight{ 1024.0f };
	const glm::vec3 Camera::m_DefaultLookAt{ 0.0f };

	Camera::Camera(Object * object, bool isUseClientSize, CameraType type, bool isEnableGBuffer) :
		Component(object),
		m_isEnableFrustumCulling(true),
		m_isUseClientSize(isUseClientSize),
		m_type(type),
		m_direction(0.0f, 0.0f, -1.0f),
		m_viewMatrix(1.0f),
		m_projMatrix(1.0f),
		m_viewProjMatrix(1.0f),
		m_outputParam(new OutputParam()),
		m_gBufferOutput((isEnableGBuffer) ? new GBufferOutput() : nullptr),
		m_orbitControls(nullptr)
	{
		Core::GetRender()->AddCamera(this, m_type);

		m_isPerspective.Set(m_DefaultIsPerspective);
		m_zoom.Set(m_DefaultZoom);
		m_fov.Set(m_DefaultFov);
		m_near.Set(m_DefaultNear);
		m_far.Set(m_DefaultFar);
		m_lookAt.Set(m_DefaultLookAt);

		SetSize((m_isUseClientSize) ? Core::GetWindow()->GetClientSize() : glm::vec2(m_DefaultWidth, m_DefaultHeight));

		UpdateViewMatrix();
		UpdateProjMatrix();
	}

	Camera::~Camera()
	{
		Core::GetRender()->RemoveCamera(this, m_type);
		AN_DELETE(m_outputParam);
		AN_DELETE(m_framebuffer);
		AN_DELETE(m_depthTexture);
		AN_DELETE(m_orbitControls);
	}

	bool Camera::OnUpdate()
	{
		bool isMatrixChanged{ false };

		if (GetObject()->GetTransform()->GetIsChangedMatrix() ||
			m_lookAt.Check())
		{
			UpdateViewMatrix();
			isMatrixChanged = true;

			m_direction = glm::normalize(m_lookAt.Get() - GetObject()->GetTransform()->GetWorldPosition());

			m_lookAt.Reset();
		}

		if (m_isPerspective.Check() ||
			m_zoom.Check() ||
			m_fov.Check() ||
			m_near.Check() ||
			m_far.Check() ||
			m_width.Check() ||
			m_height.Check())
		{
			UpdateProjMatrix();
			isMatrixChanged = true;

			m_isPerspective.Reset();
			m_zoom.Reset();
			m_fov.Reset();
			m_near.Reset();
			m_far.Reset();
			m_width.Reset();
			m_height.Reset();
		}

		if (isMatrixChanged) { m_viewProjMatrix = m_projMatrix * m_viewMatrix; }

		return true;
	}

	void Camera::OnWindowResize()
	{
		if (m_isUseClientSize &&
			Core::GetWindow()->GetClientSize().x > 0 &&
			Core::GetWindow()->GetClientSize().y > 0)
		{
			SetSize(Core::GetWindow()->GetClientSize());
		}
	}

	bool Camera::InitializeGBuffer()
	{
		if (m_gBufferOutput) { return m_gBufferOutput->Initialize(); }
		else { return false; }
	}

	bool Camera::CheckFrustum(const glm::vec3 & worldPosition, float radius)
	{
		// TODO
		return true;
	}

	bool Camera::CreateFramebuffer()
	{
		unsigned framebufferId{ 0 };

		GL_CHECK(glGenFramebuffers(1, &framebufferId));

		m_framebuffer = new Framebuffer(framebufferId);

		m_outputParam->m_frameBufferId = m_framebuffer->GetId();

		return true;
	}

	bool Camera::CreateDepthTexture()
	{
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer->GetId()));

		unsigned textureId{ 0 };
		GL_CHECK(glGenTextures(1, &textureId));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, static_cast<int>(m_width.Get()), static_cast<int>(m_height.Get()), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));

		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

		m_depthTexture = new Texture(textureId, static_cast<unsigned>(m_width.Get()), static_cast<unsigned>(m_height.Get()));

		GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->GetId(), 0));

		GL_CHECK(glDrawBuffer(GL_NONE));
		GL_CHECK(glReadBuffer(GL_NONE));

		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		return true;
	}

	void Camera::SetSize(const glm::vec2 & size)
	{
		m_width.Set(size.x);
		m_height.Set(size.y);

		m_outputParam->m_viewport.z = static_cast<int>(m_width.Get());
		m_outputParam->m_viewport.w = static_cast<int>(m_height.Get());
	}

	void Camera::SetOffset(const glm::ivec2 & offset)
	{
		m_outputParam->m_viewport.x = offset.x;
		m_outputParam->m_viewport.y = offset.y;
	}

	void Camera::UpdateViewMatrix()
	{
		m_viewMatrix = glm::lookAt(GetObject()->GetTransform()->GetWorldPosition(), m_lookAt.Get(), GetObject()->GetTransform()->GetLookAt(glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	void Camera::UpdateProjMatrix()
	{
		if (m_isPerspective.Get())
		{
			m_projMatrix = glm::perspective(m_fov.Get(), m_width.Get() / m_height.Get(), m_near.Get(), m_far.Get());
		}
		else
		{
			m_projMatrix = glm::ortho(m_width.Get() / m_zoom.Get(), m_height.Get() / m_zoom.Get(), m_near.Get(), m_far.Get());
		}
	}

}