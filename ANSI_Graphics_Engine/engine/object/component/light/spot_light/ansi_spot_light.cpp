#include "ansi_spot_light.h"

#include "core/log/ansi_log.h"
#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace AN
{

	SpotLight::SpotLight(Object * object, float radius, float angle, float smoothRange, const glm::vec3 & color) :
		Component(object),
		m_radius(radius),
		m_radiusRcp(1.0f / glm::max(m_radius, std::numeric_limits<float>::min())),
		m_smoothRangeRcp(1.0f / glm::clamp(smoothRange, std::numeric_limits<float>::min(), 1.0f)),
		m_angle(angle),
		m_cosAngle(glm::cos(glm::radians(glm::clamp(m_angle * 0.5f, 0.0f, 67.5f)))),
		m_color(glm::clamp(color * color, glm::vec3(0.0f), glm::vec3(1.0f))),
		m_shadowMapCamera(nullptr)
	{

	}

	SpotLight::~SpotLight()
	{
		AN_DELETE(m_shadowMapCamera);
	}

	bool SpotLight::OnUpdate()
	{
		if (!m_shadowMapCamera) { return true; }

		if (GetObject()->GetTransform()->GetIsChangedMatrix())
		{
			m_shadowMapCamera->SetLookAt(GetObject()->GetTransform()->GetWorldPosition() + GetObject()->GetTransform()->GetLookAt());
		}
		m_shadowMapCamera->SetFov(glm::radians(m_angle));
		m_shadowMapCamera->SetFar(m_radius);

		AN_CHECK(m_shadowMapCamera->OnUpdate());

		return true;
	}

	bool SpotLight::CastShadow()
	{
		m_shadowMapCamera = new Camera(GetObject(), false, CameraType::Light);
		m_shadowMapCamera->SetSize(glm::vec2(1024.0f));

		AN_CHECK(m_shadowMapCamera->CreateFramebuffer());
		AN_CHECK(m_shadowMapCamera->CreateDepthTexture());

		return true;
	}

}
