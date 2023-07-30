#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class PointLights3Material : public AN::Material
	{
	public:
		explicit PointLights3Material(AN::Shader * shader, AN::PointLight ** lights);

		bool OnUpdateUniforms() override;

		void SetSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
		void SetSpecularPower(float specularPower) { m_specularPower = specularPower; }

	private:
		AN::PointLight * m_lights[3];

	};

}
