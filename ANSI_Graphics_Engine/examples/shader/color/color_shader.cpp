#include "color_shader.h"

namespace Example
{

	ColorShader::ColorShader(AN::Shader * shader, AN::Object * object) :
		ShaderParam(shader),
		m_color(1.0f),
		m_object(object),
		m_MVP(1.0f)
	{

	}

	bool ColorShader::OnUpdateUniforms()
	{
		m_MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		// Vertex
		AN_CHECK(SetUniform4x4f("u_MVP", m_MVP));

		// Fragment
		AN_CHECK(SetUniform4f("u_color", m_color));

		return true;
	}

}
