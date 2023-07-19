#include "ansi_depth_map_shader.h"

#include "core/render/ansi_render.h"
#include "core/render/built_in_resources/ansi_built_in_resources.h"

namespace AN
{

	DepthMapShader::DepthMapShader() :
		ShaderParam(Core::GetRender()->GetBuiltInResources()->GetDepthMapShader())
	{

	}

	bool DepthMapShader::OnUpdateUniforms()
	{
		// TODO
		return true;
	}

}
