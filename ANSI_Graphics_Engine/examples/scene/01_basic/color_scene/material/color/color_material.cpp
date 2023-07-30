#include "color_material.h"

namespace Example
{

	ColorMaterial::ColorMaterial(AN::Shader * shader) :
		Material(shader)
	{

	}

	bool ColorMaterial::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));

		/* === Fragment === */
		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		return true;
	}

}
