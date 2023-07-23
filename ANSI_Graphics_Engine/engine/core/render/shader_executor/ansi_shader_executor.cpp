#include "ansi_shader_executor.h"

#include "object/component/renderer/shader_param/ansi_shader_param.h"
#include "resource/shader/ansi_shader.h"
#include "resource/texture/ansi_texture.h"

namespace AN
{

	ShaderExecutor::ShaderExecutor()
	{
		Reset();
	}

	bool ShaderExecutor::Apply(ShaderParam * param)
	{
		m_shaderId.Set(param->m_shader->GetId());
		for (unsigned i{ 0 }; i < MaximumTextureCount; ++i) { m_textureIds.Set(i, param->m_textureIds[i]); }

		if (m_shaderId.Check())
		{
			m_shaderId.Reset();
			GL_CHECK(glUseProgram(m_shaderId.Get()));
		}

		if (m_textureIds.Check())
		{
			for (int i{ m_textureIds.GetStart() }; i <= m_textureIds.GetEnd(); ++i)
			{
				GL_CHECK(glActiveTexture(GL_TEXTURE0 + i));
				GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureIds.Get(i)));
			}
			m_textureIds.Reset();
		}

		AN_CHECK(param->OnUpdateUniforms());

		return true;
	}

	void ShaderExecutor::Reset()
	{
		m_shaderId.Set(0);
		m_textureIds.SetAll(0);

		m_shaderId.Reset();
		m_textureIds.Reset();
	}

}
