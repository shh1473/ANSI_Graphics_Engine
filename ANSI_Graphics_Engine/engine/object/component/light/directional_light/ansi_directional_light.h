#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class DirectionalLight : public Component
	{
	public:
		explicit DirectionalLight(Object * object, const glm::vec3 & color = glm::vec3(1.0f));

		void SetColor(const glm::vec3 & color) { m_color = color * color; }

		const glm::vec3 & GetColor() const { return m_color; }

	private:
		glm::vec3 m_color;

	};

}
