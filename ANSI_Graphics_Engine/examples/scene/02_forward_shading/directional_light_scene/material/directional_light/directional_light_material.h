#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class DirectionalLightMaterial : public AN::Material
	{
	public:
		explicit DirectionalLightMaterial(AN::Shader * shader, AN::DirectionalLight * light);

		bool OnUpdateUniforms() override;

		void SetSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
		void SetSpecularPower(float specularPower) { m_specularPower = specularPower; }

	private:
		AN::DirectionalLight * m_light;

	};

}
