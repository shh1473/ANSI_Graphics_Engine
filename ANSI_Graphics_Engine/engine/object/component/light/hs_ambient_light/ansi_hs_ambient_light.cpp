#include "ansi_hs_ambient_light.h"

#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"

namespace AN
{

	HSAmbientLight::HSAmbientLight(Object * object, const glm::vec3 & upColor, const glm::vec3 & downColor) :
		Component(object),
		m_upColor(glm::max(glm::vec3(0.0f), upColor * upColor)),
		m_downColor(glm::max(glm::vec3(0.0f), downColor * downColor)),
		m_colorRange(m_upColor - m_downColor)
	{

	}

}
