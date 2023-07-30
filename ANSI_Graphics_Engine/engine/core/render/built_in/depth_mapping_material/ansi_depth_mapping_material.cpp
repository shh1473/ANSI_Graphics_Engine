#include "ansi_depth_mapping_material.h"

#include "core/render/ansi_render.h"
#include "core/render/built_in/ansi_built_in.h"

namespace AN
{

	DepthMappingMaterial::DepthMappingMaterial() :
		Material(nullptr)
	{

	}

	bool DepthMappingMaterial::OnUpdateUniforms()
	{
		// TODO
		return true;
	}

}
