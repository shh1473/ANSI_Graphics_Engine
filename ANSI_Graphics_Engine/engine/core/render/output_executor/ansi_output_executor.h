#pragma once

#include "output_param/ansi_output_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class OutputExecutor
	{
	public:
		explicit OutputExecutor();

		bool Apply(OutputParam * param);
		void Reset();

	private:
		StateChecker<int> m_clearStencil;
		StateChecker<float> m_clearDepth;
		StateChecker<glm::vec4> m_clearColor;
		StateChecker<glm::ivec4> m_viewport;
		StateChecker<MSAA> m_msaa;
		StateChecker<unsigned> m_frameBufferId;

	};

}
