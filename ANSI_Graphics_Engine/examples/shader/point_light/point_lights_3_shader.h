#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class PointLights3Shader : public AN::ShaderParam
	{
	public:
		explicit PointLights3Shader(AN::Shader * shader, AN::Object * object, AN::PointLight ** pointLights);

		bool OnUpdateUniforms() override;

	private:
		AN::Object * m_object;
		AN::PointLight * m_pointLights[3];
		glm::mat4 m_MVP;

	};

}
