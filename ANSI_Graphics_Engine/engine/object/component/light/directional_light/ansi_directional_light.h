#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class DirectionalLight : public Component
	{
	public:
		explicit DirectionalLight(Object * object, const glm::vec3 & color = glm::vec3(1.0f), const glm::vec3 & direction = glm::vec3(0.0f, -1.0f, 0.0f));

		void LookAt(const glm::vec3 & target);

		void SetSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
		void SetSpecularPower(float specularPower) { m_specularPower = specularPower; }
		void SetColor(const glm::vec3 & color) { m_color = color; }
		void SetDirection(const glm::vec3 & direction) { m_direction = glm::normalize(direction); }

		float GetSpecularIntensity() const { return m_specularIntensity; }
		float GetSpecularPower() const { return m_specularPower; }
		const glm::vec3 & GetColor() const { return m_color; }
		const glm::vec3 & GetDirection() const { return m_direction; }

	private:
		float m_specularIntensity;
		float m_specularPower;
		glm::vec3 m_color;
		glm::vec3 m_direction;

	};

}
