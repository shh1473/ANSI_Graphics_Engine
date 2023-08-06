#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class DepthSpotCamera;

	class SpotLight : public Component
	{
	public:
		explicit SpotLight(Object * object, float radius, float angle, float smoothRange, const glm::vec3 & color = glm::vec3(1.0f));
		virtual ~SpotLight();

		bool OnUpdate() override;

		bool CastShadow();

		void SetRadius(float radius);
		void SetAngle(float angle);
		void SetSmoothRange(float smoothRange) { m_smoothRangeRcp = 1.0f / glm::clamp(smoothRange, 0.001f, 1.0f); }
		void SetColor(const glm::vec3 & color) { m_color = glm::clamp(color * color, glm::vec3(0.0f), glm::vec3(1.0f)); }

		float GetRadiusRcp() const { return m_radiusRcp; }
		float GetSmoothRangeRcp() const { return m_smoothRangeRcp; }
		float GetCosAngle() const { return m_cosAngle; }
		const glm::vec3 & GetColor() const { return m_color; }
		DepthSpotCamera * GetShadowMapCamera() const { return m_shadowMapCamera; }

	private:
		float m_radius;
		float m_radiusRcp;
		float m_smoothRangeRcp;
		float m_angle;
		float m_cosAngle;
		glm::vec3 m_color;
		DepthSpotCamera * m_shadowMapCamera;

	};

}
