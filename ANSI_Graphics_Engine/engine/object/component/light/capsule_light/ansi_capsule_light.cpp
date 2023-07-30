#include "ansi_capsule_light.h"

#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"

namespace AN
{

	CapsuleLight::CapsuleLight(Object * object, float radius, float length, const glm::vec3 & direction, const glm::vec3 & color) :
		Component(object),
		m_radiusRcp(1.0f / radius),
		m_halfLength(length * 0.5f),
		m_color(color * color),
		m_direction(direction)
	{

	}

}
