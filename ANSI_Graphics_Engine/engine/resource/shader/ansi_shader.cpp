#include "ansi_shader.h"

namespace AN
{

	Shader::Shader(unsigned id, RenderType type) :
		m_id(id),
		m_type(type)
	{

	}

	Shader::~Shader()
	{
		GL_ERROR_LOG(glUseProgram(0));
		GL_ERROR_LOG(glDeleteProgram(m_id));
	}

}
