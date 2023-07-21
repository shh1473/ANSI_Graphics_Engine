#include "ansi_directional_light.h"

#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace AN
{

	DirectionalLight::DirectionalLight(Object * object, const glm::vec3 & color, const glm::vec3 & direction) :
		Component(object),
		m_specularIntensity(1.0f),
		m_specularPower(32.0f),
		m_color(color * color),
		m_direction(direction)
	{

	}

	void DirectionalLight::LookAt(const glm::vec3 & target)
	{
		m_direction = glm::normalize(target - GetObject()->GetTransform()->GetPosition());
	}

}
