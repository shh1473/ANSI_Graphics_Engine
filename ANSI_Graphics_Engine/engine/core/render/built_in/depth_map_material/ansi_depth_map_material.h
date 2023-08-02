#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace AN
{

	class Shader;

	class DepthMapMaterial : public Material
	{
	public:
		explicit DepthMapMaterial(Shader * shader);

		bool OnUpdateUniforms() override;

	};

}
