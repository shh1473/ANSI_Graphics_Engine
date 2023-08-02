#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class PointLight : public Component
	{
	public:
		explicit PointLight(Object * object, float radius, const glm::vec3 & color = glm::vec3(1.0f));

		void SetRadius(float radius) { m_radiusRcp = 1.0f / glm::max(radius, std::numeric_limits<float>::min()); }
		void SetColor(const glm::vec3 & color) { m_color = glm::clamp(color * color, glm::vec3(0.0f), glm::vec3(1.0f)); }

		float GetRadiusRcp() const { return m_radiusRcp; }
		const glm::vec3 & GetColor() const { return m_color; }

	private:
		float m_radiusRcp;
		glm::vec3 m_color;

	};

}
