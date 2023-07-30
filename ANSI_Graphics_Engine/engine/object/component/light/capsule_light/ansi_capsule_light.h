#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class CapsuleLight : public Component
	{
	public:
		explicit CapsuleLight(Object * object, float radius, float length,
			const glm::vec3 & direction = glm::vec3(0.0f, 1.0f, 0.0f),
			const glm::vec3 & color = glm::vec3(1.0f));

		void SetRadius(float radius) { if (radius != 0.0f) { m_radiusRcp = 1.0f / radius; } else { m_radiusRcp = std::numeric_limits<float>::max(); } }
		void SetLength(float length) { m_halfLength = length * 0.5f; }
		void SetColor(const glm::vec3 & color) { m_color = color; }
		void SetDirection(const glm::vec3 & direction) { m_direction = direction; }

		float GetRadiusRcp() const { return m_radiusRcp; }
		float GetHalfLength() const { return m_halfLength; }
		const glm::vec3 & GetColor() const { return m_color; }
		const glm::vec3 & GetDirection() const { return m_direction; }

	private:
		float m_radiusRcp;
		float m_halfLength;
		glm::vec3 m_color;
		glm::vec3 m_direction;

	};

}
