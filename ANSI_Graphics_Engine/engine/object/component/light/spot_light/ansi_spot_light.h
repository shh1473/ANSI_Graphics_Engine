#pragma once

#include "object/component/camera/ansi_camera.h"

namespace AN
{

	class SpotLight : public Component
	{
	public:
		explicit SpotLight(Object * object, float radius, float angle, float smoothRange, const glm::vec3 & color = glm::vec3(1.0f));
		~SpotLight();

		bool OnUpdate() override;

		bool CastShadow();

		void SetRadius(float radius) { m_radiusRcp = 1.0f / (m_radius = glm::max(radius, std::numeric_limits<float>::min())); }
		void SetSmoothRange(float smoothRange) { m_smoothRangeRcp = 1.0f / glm::clamp(smoothRange, 0.001f, 1.0f); }
		void SetAngle(float angle) { m_cosAngle = glm::cos(glm::radians(glm::clamp((m_angle = angle) * 0.5f, 0.0f, 67.5f))); }
		void SetColor(const glm::vec3 & color) { m_color = glm::clamp(color * color, glm::vec3(0.0f), glm::vec3(1.0f)); }

		float GetRadiusRcp() const { return m_radiusRcp; }
		float GetSmoothRangeRcp() const { return m_smoothRangeRcp; }
		float GetCosAngle() const { return m_cosAngle; }
		const glm::vec3 & GetColor() const { return m_color; }
		Camera * GetShadowMapCamera() const { return m_shadowMapCamera; }

	private:
		float m_radius;
		float m_radiusRcp;
		float m_smoothRangeRcp;
		float m_angle;
		float m_cosAngle;
		glm::vec3 m_color;
		Camera * m_shadowMapCamera;

	};

}
