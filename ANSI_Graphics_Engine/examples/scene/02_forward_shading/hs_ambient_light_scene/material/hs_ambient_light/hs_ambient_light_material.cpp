#include "hs_ambient_light_material.h"

namespace Example
{

	HSAmbientLightMaterial::HSAmbientLightMaterial(AN::Shader * shader, AN::HSAmbientLight * light) :
		Material(shader),
		m_light(light)
	{

	}

	bool HSAmbientLightMaterial::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_transform->GetWorldMatrix()));

		/* === Fragment === */
		AN_CHECK(SetUniform3f("u_downColor", m_light->GetDownColor()));
		AN_CHECK(SetUniform3f("u_colorRange", m_light->GetColorRange()));

		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		return true;
	}

}
