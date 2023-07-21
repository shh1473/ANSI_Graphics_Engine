#include "ansi_ambient_light.h"

#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"

namespace AN
{

	AmbientLight::AmbientLight(Object * object, const glm::vec3 & upColor, const glm::vec3 & downColor) :
		Component(object),
		m_downColor(downColor * downColor),
		m_colorRange((upColor * upColor) - m_downColor)
	{

	}

}
