#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ColorShader : public AN::ShaderParam
	{
	public:
		explicit ColorShader(AN::Shader * shader, AN::Object * object);

		bool OnUpdateUniforms() override;

		void SetColor(const glm::vec3 & color) { m_color = color; }

		const glm::vec3 & GetColor() const { return m_color; }

	private:
		glm::vec3 m_color;
		AN::Object * m_object;

	};

}
