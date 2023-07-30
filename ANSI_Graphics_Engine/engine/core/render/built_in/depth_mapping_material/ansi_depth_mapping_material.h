#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace AN
{

	class DepthMappingMaterial : public Material
	{
	public:
		explicit DepthMappingMaterial();

		bool OnUpdateUniforms() override;

	};

}
