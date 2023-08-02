#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class SpotShadows3Material : public AN::Material
	{
	public:
		explicit SpotShadows3Material(AN::Shader * shader, AN::SpotLight ** lights);

		bool OnUpdateUniforms() override;

	private:
		AN::SpotLight * m_lights[3];

	};

}
