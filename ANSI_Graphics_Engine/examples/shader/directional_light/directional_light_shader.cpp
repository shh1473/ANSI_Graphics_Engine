#include "directional_light_shader.h"

namespace Example
{

	DirectionalLightShader::DirectionalLightShader(AN::Shader * shader, AN::Object * object, AN::DirectionalLight * directionalLight) :
		ShaderParam(shader),
		m_object(object),
		m_directionalLight(directionalLight),
		m_MVP(1.0f)
	{

	}

	bool DirectionalLightShader::OnUpdateUniforms()
	{
		m_MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		// Vertex
		AN_CHECK(SetUniform4x4f("u_MVP", m_MVP));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_object->GetTransform()->GetWorldMatrix()));

		// Fragment
		AN_CHECK(SetUniform1f("u_specularIntensity", m_directionalLight->GetSpecularIntensity()));
		AN_CHECK(SetUniform1f("u_specularPower", m_directionalLight->GetSpecularPower()));
		AN_CHECK(SetUniform3f("u_color", m_directionalLight->GetColor()));
		AN_CHECK(SetUniform3f("u_lightDirection", m_directionalLight->GetDirection()));
		AN_CHECK(SetUniform3f("u_cameraDirection", AN::Core::GetRender()->GetCurrentCamera()->GetDirection()));

		return true;
	}

}
