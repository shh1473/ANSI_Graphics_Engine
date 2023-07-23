#include "directional_light_shader.h"

#include "utility/converter/ansi_converter.h"

namespace Example
{

	DirectionalLightShader::DirectionalLightShader(AN::Shader * shader, AN::Object * object, AN::DirectionalLight * directionalLight) :
		ShaderParam(shader),
		m_object(object),
		m_directionalLight(directionalLight)
	{

	}

	bool DirectionalLightShader::OnUpdateUniforms()
	{
		/* === Vertex === */
		static glm::mat4 MVP(1.0f);
		MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		AN_CHECK(SetUniform4x4f("u_MVP", MVP));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_object->GetTransform()->GetWorldMatrix()));

		/* === Fragment === */
		static glm::vec3 direction(0.0f);
		direction = glm::mat3_cast(AN::Converter::EulerXYZToQuat(m_directionalLight->GetObject()->GetTransform()->GetRotation())) * glm::vec3(0.0f, 0.0f, 1.0f);

		AN_CHECK(SetUniform1f("u_specularIntensity", m_directionalLight->GetSpecularIntensity()));
		AN_CHECK(SetUniform1f("u_specularPower", m_directionalLight->GetSpecularPower()));
		AN_CHECK(SetUniform3f("u_lightColor", m_directionalLight->GetColor()));
		AN_CHECK(SetUniform3f("u_lightDirection", direction));
		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		return true;
	}

}
