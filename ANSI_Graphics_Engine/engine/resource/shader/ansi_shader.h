#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class Shader
	{
	public:
		explicit Shader(unsigned id, RenderType type);
		virtual ~Shader();

		unsigned GetId() const { return m_id; }
		RenderType GetType() const { return m_type; }

	private:
		const unsigned m_id;
		const RenderType m_type;

	};

}
