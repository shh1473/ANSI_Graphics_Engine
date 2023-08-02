#include "ansi_framebuffer.h"

namespace AN
{

	Framebuffer::Framebuffer(unsigned id) :
		m_id(id)
	{

	}

	Framebuffer::~Framebuffer()
	{
		GL_ERROR_LOG(glDeleteFramebuffers(1, &m_id));
	}

}
