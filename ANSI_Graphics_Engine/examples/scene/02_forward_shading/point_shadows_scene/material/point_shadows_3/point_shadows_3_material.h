#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class PointShadows3Material : public AN::Material
	{
	public:
		explicit PointShadows3Material(AN::Shader * shader, AN::PointLight ** lights);

		bool OnUpdateUniforms() override;

		void SetCullMode(AN::CullMode cullMode) { m_cullMode = cullMode; }

	private:
		AN::PointLight * m_lights[3];

	};

}
