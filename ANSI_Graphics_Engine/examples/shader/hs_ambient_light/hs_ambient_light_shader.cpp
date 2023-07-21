#include "hs_ambient_light_shader.h"

namespace Example
{

	HemiSphereAmbientLightShader::HemiSphereAmbientLightShader(AN::Shader * shader, AN::Object * object, AN::AmbientLight * ambientLight) :
		ShaderParam(shader),
		m_object(object),
		m_ambientLight(ambientLight),
		m_MVP(1.0f)
	{

	}

	bool HemiSphereAmbientLightShader::OnUpdateUniforms()
	{
		m_MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		// Vertex
		AN_CHECK(SetUniform4x4f("u_MVP", m_MVP));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_object->GetTransform()->GetWorldMatrix()));

		// Fragment
		AN_CHECK(SetUniform3f("u_downColor", m_ambientLight->GetDownColor()));
		AN_CHECK(SetUniform3f("u_colorRange", m_ambientLight->GetColorRange()));

		return true;
	}

}
