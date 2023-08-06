#include "ansi_point_light.h"

#include "core/log/ansi_log.h"
#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"
#include "resource/texture/ansi_texture.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"
#include "object/component/camera/depth_point_camera/ansi_depth_point_camera.h"

namespace AN
{

	PointLight::PointLight(Object * object, float radius, const glm::vec3 & color) :
		Component(object),
		m_radius(radius),
		m_radiusRcp(1.0f / glm::max(m_radius, std::numeric_limits<float>::min())),
		m_color(glm::clamp(color * color, glm::vec3(0.0f), glm::vec3(1.0f))),
		m_shadowMapCamera(nullptr)
	{

	}

	PointLight::~PointLight()
	{
		AN_DELETE(m_shadowMapCamera);
	}

	bool PointLight::OnUpdate()
	{
		if (!m_shadowMapCamera) { return true; }

		AN_CHECK(m_shadowMapCamera->OnUpdate());

		return true;
	}

	bool PointLight::CastShadow()
	{
		AN_CHECK_LOG(!m_shadowMapCamera);

		m_shadowMapCamera = new DepthPointCamera(GetObject());
		m_shadowMapCamera->SetSize(glm::vec2(1024.0f));
		m_shadowMapCamera->SetFov(PI * 0.5f);
		m_shadowMapCamera->SetFar(glm::max(m_radius, 1.0f));

		AN_CHECK(m_shadowMapCamera->CreateFramebuffer());
		AN_CHECK(m_shadowMapCamera->CreateDepthMap());

		return true;
	}

	void PointLight::SetRadius(float radius)
	{
		m_radius = glm::max(radius, std::numeric_limits<float>::min());
		m_radiusRcp = 1.0f / m_radius;
		if (m_shadowMapCamera) { m_shadowMapCamera->SetFar(glm::max(m_radius, 1.0f)); }
	}

}
