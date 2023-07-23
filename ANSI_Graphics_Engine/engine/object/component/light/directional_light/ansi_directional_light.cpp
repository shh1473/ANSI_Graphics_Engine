#include "ansi_directional_light.h"

#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace AN
{

	DirectionalLight::DirectionalLight(Object * object, const glm::vec3 & color) :
		Component(object),
		m_specularIntensity(1.0f),
		m_specularPower(32.0f),
		m_color(color * color)
	{

	}

}
