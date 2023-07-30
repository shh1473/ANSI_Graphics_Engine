#include "texture_material.h"

namespace Example
{

	TextureMaterial::TextureMaterial(AN::Shader * shader) :
		Material(shader)
	{

	}

	bool TextureMaterial::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));

		/* === Fragment === */
		AN_CHECK(SetUniform1i("u_diffuseMap", 0));
		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		return true;
	}

}
