#include "color_shader.h"

namespace Example
{

	ColorShader::ColorShader(AN::Shader * shader, AN::Object * object) :
		ShaderParam(shader),
		m_color(1.0f),
		m_object(object)
	{

	}

	bool ColorShader::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix()));

		/* === Fragment === */
		AN_CHECK(SetUniform3f("u_color", m_color));

		return true;
	}

}
