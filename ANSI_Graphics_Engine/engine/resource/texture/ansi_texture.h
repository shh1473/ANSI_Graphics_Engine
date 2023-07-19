#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Texture
	{
	public:
		explicit Texture(unsigned id, unsigned width, unsigned height);
		virtual ~Texture();

		unsigned GetId() const { return m_id; }
		unsigned GetWidth() const { return m_width; }
		unsigned GetHeight() const { return m_height; }

	private:
		const unsigned m_id;
		const unsigned m_width;
		const unsigned m_height;

	};

}
