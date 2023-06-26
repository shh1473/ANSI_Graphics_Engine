#include "ansi_shader.h"

namespace AN
{

	Shader::Shader(unsigned resourceId) :
		Resource(resourceId)
	{

	}

	Shader::~Shader()
	{
		GL_ERROR_LOG(glDeleteProgram(m_resourceId));
	}

}
