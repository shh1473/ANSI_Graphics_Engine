#include "ansi_shader_executor.h"

#include "object/component/renderer/shader_param/ansi_shader_param.h"

namespace AN
{

	ShaderExecutor::ShaderExecutor()
	{
		m_shaderId.Set(0);

		m_shaderId.Reset();
	}

	bool ShaderExecutor::Apply(ShaderParam * param)
	{
		m_shaderId.Set(param->m_shaderId);

		if (m_shaderId.Check())
		{
			m_shaderId.Reset();
			GL_CHECK(glUseProgram(m_shaderId.Get()));
		}

		for (const auto & uniform : param->m_uniforms1i)
		{
			GL_CHECK(glUniform1i(param->GetUniformLocation(uniform.first), uniform.second));
		}

		for (const auto & uniform : param->m_uniforms1f)
		{
			GL_CHECK(glUniform1f(param->GetUniformLocation(uniform.first), uniform.second));
		}

		for (const auto & uniform : param->m_uniforms2f)
		{
			GL_CHECK(glUniform2f(param->GetUniformLocation(uniform.first), uniform.second.x, uniform.second.y));
		}

		for (const auto & uniform : param->m_uniforms3f)
		{
			GL_CHECK(glUniform3f(param->GetUniformLocation(uniform.first), uniform.second.x, uniform.second.y, uniform.second.z));
		}

		for (const auto & uniform : param->m_uniforms4f)
		{
			GL_CHECK(glUniform4f(param->GetUniformLocation(uniform.first), uniform.second.x, uniform.second.y, uniform.second.z, uniform.second.w));
		}

		for (const auto & uniform : param->m_uniforms4fv)
		{
			GL_CHECK(glUniformMatrix4fv(param->GetUniformLocation(uniform.first), 1, GL_FALSE, &uniform.second[0][0]));
		}

		return true;
	}

}
