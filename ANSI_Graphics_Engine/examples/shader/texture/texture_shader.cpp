#include "texture_shader.h"

namespace Example
{

	TextureShader::TextureShader(AN::Shader * shader, AN::Object * object) :
		ShaderParam(shader),
		m_object(object),
		m_MVP(1.0f)
	{

	}

	bool TextureShader::OnUpdateUniforms()
	{
		m_MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		// Vertex
		AN_CHECK(SetUniform4x4f("u_MVP", m_MVP));

		// Fragment
		AN_CHECK(SetUniform1i("u_diffuseMap", 0));

		return true;
	}

}
