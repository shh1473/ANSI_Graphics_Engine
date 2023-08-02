#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Framebuffer
	{
	public:
		explicit Framebuffer(unsigned id);
		virtual ~Framebuffer();

		unsigned GetId() const { return m_id; }

	private:
		const unsigned m_id;

	};

}
