#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class CapsuleLights3Shader : public AN::ShaderParam
	{
	public:
		explicit CapsuleLights3Shader(AN::Shader * shader, AN::Object * object, AN::CapsuleLight ** capsuleLights);

		bool OnUpdateUniforms() override;

	private:
		AN::Object * m_object;
		AN::CapsuleLight * m_capsuleLights[3];

	};

}
