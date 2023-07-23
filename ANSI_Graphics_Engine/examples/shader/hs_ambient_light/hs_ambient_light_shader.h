#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class HemisphereAmbientLightShader : public AN::ShaderParam
	{
	public:
		explicit HemisphereAmbientLightShader(AN::Shader * shader, AN::Object * object, AN::AmbientLight * ambientLight);

		bool OnUpdateUniforms() override;

	private:
		AN::Object * m_object;
		AN::AmbientLight * m_ambientLight;

	};

}
