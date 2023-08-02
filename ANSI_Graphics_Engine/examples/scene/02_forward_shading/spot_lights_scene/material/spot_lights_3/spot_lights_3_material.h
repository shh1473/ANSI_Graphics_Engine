#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class SpotLights3Material : public AN::Material
	{
	public:
		explicit SpotLights3Material(AN::Shader * shader, AN::SpotLight ** lights);

		bool OnUpdateUniforms() override;

		void SetSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
		void SetSpecularPower(float specularPower) { m_specularPower = specularPower; }

	private:
		AN::SpotLight * m_lights[3];

	};

}
