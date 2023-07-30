#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class HSAmbientLightMaterial : public AN::Material
	{
	public:
		explicit HSAmbientLightMaterial(AN::Shader * shader, AN::HSAmbientLight * light);

		bool OnUpdateUniforms() override;

	private:
		AN::HSAmbientLight * m_light;

	};

}
