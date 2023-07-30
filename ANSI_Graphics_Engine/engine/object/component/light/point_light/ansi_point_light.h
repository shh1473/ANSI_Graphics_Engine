#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class PointLight : public Component
	{
	public:
		explicit PointLight(Object * object, float radius, const glm::vec3 & color = glm::vec3(1.0f));

		void SetRadius(float radius) { if (radius != 0.0f) { m_radiusRcp = 1.0f / radius; } else { m_radiusRcp = std::numeric_limits<float>::max(); } }
		void SetColor(const glm::vec3 & color) { m_color = color; }

		float GetRadiusRcp() const { return m_radiusRcp; }
		const glm::vec3 & GetColor() const { return m_color; }

	private:
		float m_radiusRcp;
		glm::vec3 m_color;

	};

}
