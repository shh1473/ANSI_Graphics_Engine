#include "point_lights_3_shader.h"

#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace Example
{

	PointLights3Shader::PointLights3Shader(AN::Shader * shader, AN::Object * object, AN::PointLight ** pointLights) :
		ShaderParam(shader),
		m_object(object),
		m_pointLights{ nullptr, },
		m_MVP(1.0f)
	{
		for (unsigned i{ 0 }; i < 3; ++i) { m_pointLights[i] = pointLights[i]; }
	}

	bool PointLights3Shader::OnUpdateUniforms()
	{
		static float radiusRcp[3];
		static float specularIntensities[3];
		static float specularPowers[3];
		static glm::vec3 colors[3];
		static glm::vec3 positions[3];
		
		m_MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		// Vertex
		AN_CHECK(SetUniform4x4f("u_MVP", m_MVP));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_object->GetTransform()->GetWorldMatrix()));

		// Fragment
		for (unsigned i{ 0 }; i < 3; ++i)
		{
			radiusRcp[i] = m_pointLights[i]->GetRadiusRcp();
			specularIntensities[i] = m_pointLights[i]->GetSpecularIntensity();
			specularPowers[i] = m_pointLights[i]->GetSpecularPower();
			colors[i] = m_pointLights[i]->GetColor();
			positions[i] = m_pointLights[i]->GetObject()->GetTransform()->GetWorldPosition();
		}

		AN_CHECK(SetUniform1fv("u_radiusRcp", 3, &radiusRcp[0]));
		AN_CHECK(SetUniform1fv("u_specularIntensities", 3, &specularIntensities[0]));
		AN_CHECK(SetUniform1fv("u_specularPowers", 3, &specularPowers[0]));
		AN_CHECK(SetUniform3fv("u_colors", 3, &colors[0].x));
		AN_CHECK(SetUniform3fv("u_positions", 3, &positions[0].x));
		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		return true;
	}

}
