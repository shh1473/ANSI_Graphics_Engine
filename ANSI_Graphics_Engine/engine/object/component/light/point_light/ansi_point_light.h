#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class DepthPointCamera;

	class PointLight : public Component
	{
	public:
		explicit PointLight(Object * object, float radius, const glm::vec3 & color = glm::vec3(1.0f));
		virtual ~PointLight();

		bool OnUpdate() override;

		bool CastShadow();

		void SetRadius(float radius);
		void SetColor(const glm::vec3 & color) { m_color = glm::clamp(color * color, glm::vec3(0.0f), glm::vec3(1.0f)); }

		float GetRadiusRcp() const { return m_radiusRcp; }
		const glm::vec3 & GetColor() const { return m_color; }
		DepthPointCamera * GetShadowMapCamera() { return m_shadowMapCamera; }

	private:
		float m_radius;
		float m_radiusRcp;
		glm::vec3 m_color;
		DepthPointCamera * m_shadowMapCamera;

	};

}
