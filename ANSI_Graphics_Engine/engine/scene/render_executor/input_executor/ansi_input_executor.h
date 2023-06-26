#pragma once

#include "object/component/renderer/input_param/ansi_input_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class InputExecutor
	{
	public:
		explicit InputExecutor();

		bool Apply(InputParam * param);

		PrimitiveTopology GetPrimitiveTopology() const { return m_primitiveTopology; }

	private:
		PrimitiveTopology m_primitiveTopology;
		StateChecker<unsigned> m_vertexArrayId;
		StateChecker<unsigned> m_indexBufferId;

	};

}
