#include "capsule_lights_3_material.h"

namespace Example
{

	CapsuleLights3Material::CapsuleLights3Material(AN::Shader * shader, AN::CapsuleLight ** lights) :
		Material(shader),
		m_lights{ nullptr, }
	{
		for (unsigned i{ 0 }; i < 3; ++i) { m_lights[i] = lights[i]; }
	}

	bool CapsuleLights3Material::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_transform->GetWorldMatrix()));

		/* === Fragment === */
		static float lightRadiusRcp[3];
		static float lightHalfLengths[3];
		static glm::vec3 lightColors[3];
		static glm::vec3 lightPositions[3];
		static glm::vec3 lightDirections[3];
		
		for (unsigned i{ 0 }; i < 3; ++i)
		{
			lightRadiusRcp[i] = m_lights[i]->GetRadiusRcp();
			lightHalfLengths[i] = m_lights[i]->GetHalfLength();
			lightColors[i] = m_lights[i]->GetColor();
			lightPositions[i] = m_lights[i]->GetObject()->GetTransform()->GetWorldPosition();
			lightDirections[i] = glm::mat3(m_lights[i]->GetObject()->GetTransform()->GetWorldMatrix()) * glm::vec3(0.0f, 0.0f, 1.0f);
		}

		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		AN_CHECK(SetUniform1fv("u_lightRadiusRcp", 3, &lightRadiusRcp[0]));
		AN_CHECK(SetUniform1fv("u_lightHalfLengths", 3, &lightHalfLengths[0]));
		AN_CHECK(SetUniform3fv("u_lightColors", 3, &lightColors[0].x));
		AN_CHECK(SetUniform3fv("u_lightPositions", 3, &lightPositions[0].x));
		AN_CHECK(SetUniform3fv("u_lightDirections", 3, &lightDirections[0].x));

		AN_CHECK(SetUniform1f("u_specularIntensity", m_specularIntensity));
		AN_CHECK(SetUniform1f("u_specularPower", m_specularPower));
		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		return true;
	}

}
