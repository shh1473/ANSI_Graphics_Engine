#include "ansi_shader_executor.h"

#include "object/component/renderer/shader_param/ansi_shader_param.h"
#include "resource/shader/ansi_shader.h"

namespace AN
{

	ShaderExecutor::ShaderExecutor()
	{
		m_shaderId.Set(0);

		m_shaderId.Reset();
	}

	bool ShaderExecutor::Apply(ShaderParam * param)
	{
		m_shaderId.Set(param->m_shader->GetId());

		if (m_shaderId.Check())
		{
			m_shaderId.Reset();
			GL_CHECK(glUseProgram(m_shaderId.Get()));
		}

		AN_CHECK(param->OnRender());

		return true;
	}

}
