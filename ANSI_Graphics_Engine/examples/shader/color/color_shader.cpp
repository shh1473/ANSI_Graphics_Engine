#include "color_shader.h"

namespace Example
{

	ColorShader::ColorShader(AN::Shader * shader, AN::Object * object) :
		ShaderParam(shader),
		m_object(object),
		m_color(1.0f),
		m_MVP(1.0f)
	{

	}

	bool ColorShader::OnRender()
	{
		m_MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		// Vertex
		SetUniform4x4f("u_MVP", m_MVP);

		// Fragment
		SetUniform4f("u_Color", m_color);

		return true;
	}

}
