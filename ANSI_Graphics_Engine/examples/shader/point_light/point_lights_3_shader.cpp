#include "point_lights_3_shader.h"

#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace Example
{

	PointLights3Shader::PointLights3Shader(AN::Shader * shader, AN::Object * object, AN::PointLight ** pointLights) :
		ShaderParam(shader),
		m_object(object),
		m_pointLights{ nullptr, }
	{
		for (unsigned i{ 0 }; i < 3; ++i) { m_pointLights[i] = pointLights[i]; }
	}

	bool PointLights3Shader::OnUpdateUniforms()
	{
		/* === Vertex === */
		static glm::mat4 MVP(1.0f);
		MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		AN_CHECK(SetUniform4x4f("u_MVP", MVP));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_object->GetTransform()->GetWorldMatrix()));

		/* === Fragment === */
		static float specularIntensities[3];
		static float specularPowers[3];
		static float lightRadiusRcp[3];
		static glm::vec3 lightColors[3];
		static glm::vec3 lightPositions[3];

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			lightRadiusRcp[i] = m_pointLights[i]->GetRadiusRcp();
			specularIntensities[i] = m_pointLights[i]->GetSpecularIntensity();
			specularPowers[i] = m_pointLights[i]->GetSpecularPower();
			lightColors[i] = m_pointLights[i]->GetColor();
			lightPositions[i] = m_pointLights[i]->GetObject()->GetTransform()->GetWorldPosition();
		}

		AN_CHECK(SetUniform1fv("u_specularIntensities", 3, &specularIntensities[0]));
		AN_CHECK(SetUniform1fv("u_specularPowers", 3, &specularPowers[0]));
		AN_CHECK(SetUniform1fv("u_lightRadiusRcp", 3, &lightRadiusRcp[0]));
		AN_CHECK(SetUniform3fv("u_lightColors", 3, &lightColors[0].x));
		AN_CHECK(SetUniform3fv("u_lightPositions", 3, &lightPositions[0].x));
		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		return true;
	}

}