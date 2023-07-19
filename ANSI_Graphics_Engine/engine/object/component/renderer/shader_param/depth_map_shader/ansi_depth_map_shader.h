#pragma once

#include "object/component/renderer/shader_param/ansi_shader_param.h"

namespace AN
{

	class DepthMapShader : public ShaderParam
	{
	public:
		explicit DepthMapShader();

		bool OnUpdateUniforms() override;

	};

}
