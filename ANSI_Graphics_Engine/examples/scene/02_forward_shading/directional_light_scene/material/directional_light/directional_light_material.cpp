#include "directional_light_material.h"

#include "utility/converter/ansi_converter.h"

namespace Example
{

	DirectionalLightMaterial::DirectionalLightMaterial(AN::Shader * shader, AN::DirectionalLight * light) :
		Material(shader),
		m_light(light)
	{

	}

	bool DirectionalLightMaterial::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_transform->GetWorldMatrix()));

		/* === Fragment === */
		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		AN_CHECK(SetUniform3f("u_lightColor", m_light->GetColor()));
		AN_CHECK(SetUniform3f("u_lightDirection", glm::mat3_cast(AN::Converter::EulerXYZToQuat(m_light->GetObject()->GetTransform()->GetRotation())) * glm::vec3(0.0f, 0.0f, 1.0f)));

		AN_CHECK(SetUniform1f("u_specularIntensity", m_specularIntensity));
		AN_CHECK(SetUniform1f("u_specularPower", m_specularPower));
		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		return true;
	}

}
