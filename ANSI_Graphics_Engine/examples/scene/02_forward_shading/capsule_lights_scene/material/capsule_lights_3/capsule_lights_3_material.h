#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class CapsuleLights3Material : public AN::Material
	{
	public:
		explicit CapsuleLights3Material(AN::Shader * shader, AN::CapsuleLight ** lights);

		bool OnUpdateUniforms() override;

		void SetSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
		void SetSpecularPower(float specularPower) { m_specularPower = specularPower; }

	private:
		AN::CapsuleLight * m_lights[3];

	};

}
