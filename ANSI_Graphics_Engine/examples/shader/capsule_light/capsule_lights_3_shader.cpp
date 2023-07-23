#include "capsule_lights_3_shader.h"

#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"
#include "utility/converter/ansi_converter.h"

namespace Example
{

	CapsuleLights3Shader::CapsuleLights3Shader(AN::Shader * shader, AN::Object * object, AN::CapsuleLight ** capsuleLights) :
		ShaderParam(shader),
		m_object(object),
		m_capsuleLights{ nullptr, }
	{
		for (unsigned i{ 0 }; i < 3; ++i) { m_capsuleLights[i] = capsuleLights[i]; }
	}

	bool CapsuleLights3Shader::OnUpdateUniforms()
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
		static float lightHalfLengths[3];
		static glm::vec3 lightColors[3];
		static glm::vec3 lightPositions[3];
		static glm::vec3 lightDirections[3];

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			specularIntensities[i] = m_capsuleLights[i]->GetSpecularIntensity();
			specularPowers[i] = m_capsuleLights[i]->GetSpecularPower();
			lightRadiusRcp[i] = m_capsuleLights[i]->GetRadiusRcp();
			lightHalfLengths[i] = m_capsuleLights[i]->GetHalfLength();
			lightColors[i] = m_capsuleLights[i]->GetColor();

			lightDirections[i] = glm::mat3(m_capsuleLights[i]->GetObject()->GetTransform()->GetWorldMatrix()) * glm::vec3(0.0f, 0.0f, 1.0f);
			lightPositions[i] = m_capsuleLights[i]->GetObject()->GetTransform()->GetWorldPosition();
		}

		AN_CHECK(SetUniform1fv("u_specularIntensities", 3, &specularIntensities[0]));
		AN_CHECK(SetUniform1fv("u_specularPowers", 3, &specularPowers[0]));
		AN_CHECK(SetUniform1fv("u_lightRadiusRcp", 3, &lightRadiusRcp[0]));
		AN_CHECK(SetUniform1fv("u_lightHalfLengths", 3, &lightHalfLengths[0]));
		AN_CHECK(SetUniform3fv("u_lightColors", 3, &lightColors[0].x));
		AN_CHECK(SetUniform3fv("u_lightPositions", 3, &lightPositions[0].x));
		AN_CHECK(SetUniform3fv("u_lightDirections", 3, &lightDirections[0].x));
		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		return true;
	}

}
