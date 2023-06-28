#include "ansi_camera.h"

#include "core/render/ansi_render.h"
#include "object/ansi_object.h"
#include "object/component/camera/output_param/g_buffer_output/ansi_g_buffer_output.h"

namespace AN
{

	const bool Camera::m_DefaultIsPerspective{ true };
	const float Camera::m_DefaultFov{ glm::pi<float>() * 0.25f };
	const float Camera::m_DefaultNear{ 1.0f };
	const float Camera::m_DefaultFar{ 1000.0f };
	const float Camera::m_DefaultWidth{ 1024.0f };
	const float Camera::m_DefaultHeight{ 1024.0f };

	Camera::Camera(Object * object, CameraType type, bool isEnableGBuffer) :
		Component(object),
		m_isEnableFrustumCulling(true),
		m_type(type),
		m_lookAt(0.0f),
		m_viewMatrix(1.0f),
		m_projMatrix(1.0f),
		m_viewProjMatrix(1.0f),
		m_outputParam(new OutputParam()),
		m_rasterParam(new RasterParam()),
		m_gBufferOutput((isEnableGBuffer) ? new GBufferOutput() : nullptr)
	{
		Core::GetRender()->AddCamera(this, m_type);

		m_isPerspective.Set(m_DefaultIsPerspective);
		m_fov.Set(m_DefaultFov);
		m_near.Set(m_DefaultNear);
		m_far.Set(m_DefaultFar);
		m_width.Set(m_DefaultWidth);
		m_height.Set(m_DefaultHeight);

		m_isPerspective.Reset();
		m_fov.Reset();
		m_near.Reset();
		m_far.Reset();
		m_width.Reset();
		m_height.Reset();

		UpdateViewMatrix();
		UpdateProjMatrix();
	}

	Camera::~Camera()
	{
		Core::GetRender()->RemoveCamera(this, m_type);
		AN_DELETE(m_outputParam);
		AN_DELETE(m_rasterParam);
	}

	bool Camera::OnUpdate()
	{
		bool isMatrixChanged{ false };

		if (GetObject()->GetTransform()->GetIsChangedMatrix())
		{
			UpdateViewMatrix();
			isMatrixChanged = true;
		}

		if (m_isPerspective.Check() ||
			m_fov.Check() ||
			m_near.Check() ||
			m_far.Check() ||
			m_width.Check() ||
			m_height.Check())
		{
			UpdateProjMatrix();
			isMatrixChanged = true;

			m_isPerspective.Reset();
			m_fov.Reset();
			m_near.Reset();
			m_far.Reset();
			m_width.Reset();
			m_height.Reset();
		}

		if (isMatrixChanged) { m_viewProjMatrix = m_projMatrix * m_viewMatrix; }

		return true;
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

	void Camera::UpdateViewMatrix()
	{
		m_viewMatrix = glm::lookAt(GetObject()->GetTransform()->GetWorldPosition(), m_lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::UpdateProjMatrix()
	{
		if (m_isPerspective.Get())
		{
			m_projMatrix = glm::perspective(m_fov.Get(), m_width.Get() / m_height.Get(), m_near.Get(), m_far.Get());
		}
		else
		{
			m_projMatrix = glm::ortho(m_width.Get(), m_height.Get(), m_near.Get(), m_far.Get());
		}
	}

}