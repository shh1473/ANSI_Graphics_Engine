#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class AmbientLight : public Component
	{
	public:
		explicit AmbientLight(Object * object, const glm::vec3 & upColor = glm::vec3(1.0f), const glm::vec3 & downColor = glm::vec3(0.0f));

		void SetUpColor(const glm::vec3 & color) { m_colorRange = (color * color) - m_downColor; }
		void SetDownColor(const glm::vec3 & color) { m_downColor = color * color; }

		const glm::vec3 & GetDownColor() const { return m_downColor; }
		const glm::vec3 & GetColorRange() const { return m_colorRange; }

	private:
		glm::vec3 m_downColor;
		glm::vec3 m_colorRange;

	};

}
