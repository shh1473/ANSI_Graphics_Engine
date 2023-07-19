#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class TextureShader : public AN::ShaderParam
	{
	public:
		explicit TextureShader(AN::Shader * shader, AN::Object * object);

		bool OnUpdateUniforms() override;

		void SetDiffuseMap(unsigned textureId) { SetTexture(0, textureId); }

	private:
		AN::Object * m_object;
		glm::mat4 m_MVP;

	};

}
