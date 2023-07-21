#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class DirectionalLightShader : public AN::ShaderParam
	{
	public:
		explicit DirectionalLightShader(AN::Shader * shader, AN::Object * object, AN::DirectionalLight * directionalLight);

		bool OnUpdateUniforms() override;

	private:
		AN::Object * m_object;
		AN::DirectionalLight * m_directionalLight;
		glm::mat4 m_MVP;

	};

}
