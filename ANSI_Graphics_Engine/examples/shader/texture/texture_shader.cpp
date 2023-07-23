#include "texture_shader.h"

namespace Example
{

	TextureShader::TextureShader(AN::Shader * shader, AN::Object * object) :
		ShaderParam(shader),
		m_object(object)
	{

	}

	bool TextureShader::OnUpdateUniforms()
	{
		/* === Vertex === */
		static glm::mat4 MVP(1.0f);
		MVP = AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_object->GetTransform()->GetWorldMatrix();

		AN_CHECK(SetUniform4x4f("u_MVP", MVP));

		/* === Fragment === */
		AN_CHECK(SetUniform1i("u_diffuseMap", 0));

		return true;
	}

}
