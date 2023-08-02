#include "ansi_point_light.h"

#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"

namespace AN
{

	PointLight::PointLight(Object * object, float radius, const glm::vec3 & color) :
		Component(object),
		m_radiusRcp(1.0f / glm::max(radius, std::numeric_limits<float>::min())),
		m_color(glm::clamp(color * color, glm::vec3(0.0f), glm::vec3(1.0f)))
	{

	}

}
