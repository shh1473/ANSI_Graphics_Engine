#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace AN
{

	class Shader;

	class DepthPointMaterial : public Material
	{
	public:
		explicit DepthPointMaterial(Shader * shader);

		bool OnUpdateUniforms() override;



	};

}
