#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace AN
{

	class Shader;

	class DepthSpotMaterial : public Material
	{
	public:
		explicit DepthSpotMaterial(Shader * shader);

		bool OnUpdateUniforms() override;

	};

}
