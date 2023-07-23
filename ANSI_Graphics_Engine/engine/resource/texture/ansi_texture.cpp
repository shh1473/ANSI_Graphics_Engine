#include "ansi_texture.h"

namespace AN
{

	Texture::Texture(unsigned id, unsigned width, unsigned height) :
		m_id(id),
		m_width(width),
		m_height(height)
	{

	}

	Texture::~Texture()
	{
		GL_ERROR_LOG(glDeleteTextures(1, &m_id));
	}

}
