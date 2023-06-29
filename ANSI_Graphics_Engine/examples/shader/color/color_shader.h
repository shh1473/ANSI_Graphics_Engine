#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ColorShader : public AN::ShaderParam
	{
	public:
		glm::vec4 m_color;

	public:
		explicit ColorShader(AN::Shader * shader, AN::Object * object);

		bool OnRender() override;

	private:
		AN::Object * m_object;
		glm::mat4 m_MVP;

	};

}
