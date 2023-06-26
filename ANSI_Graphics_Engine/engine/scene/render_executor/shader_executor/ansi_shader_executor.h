#pragma once

#include "object/component/renderer/shader_param/ansi_shader_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class ShaderExecutor
	{
	public:
		explicit ShaderExecutor();

		bool Apply(ShaderParam * param);

	private:
		StateChecker<unsigned> m_shaderId;

	};

}
