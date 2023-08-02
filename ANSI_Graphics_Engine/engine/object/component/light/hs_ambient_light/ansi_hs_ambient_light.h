#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class HSAmbientLight : public Component
	{
	public:
		explicit HSAmbientLight(Object * object, const glm::vec3 & upColor = glm::vec3(1.0f), const glm::vec3 & downColor = glm::vec3(1.0f));

		void SetUpColor(const glm::vec3 & color) { m_upColor = glm::max(glm::vec3(0.0f), color * color); m_colorRange = m_upColor - m_downColor; }
		void SetDownColor(const glm::vec3 & color) { m_downColor = glm::max(glm::vec3(0.0f), color * color); m_colorRange = m_upColor - m_downColor; }

		const glm::vec3 & GetDownColor() const { return m_downColor; }
		const glm::vec3 & GetColorRange() const { return m_colorRange; }

	private:
		glm::vec3 m_upColor;
		glm::vec3 m_downColor;
		glm::vec3 m_colorRange;

	};

}
