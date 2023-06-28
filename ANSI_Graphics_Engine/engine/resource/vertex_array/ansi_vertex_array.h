#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class VertexArray
	{
	public:
		explicit VertexArray(unsigned id);
		virtual ~VertexArray();

		unsigned GetId() const { return m_id; }

	private:
		unsigned m_id;

	};

}
