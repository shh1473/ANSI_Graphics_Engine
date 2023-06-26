#pragma once

#include "object/component/renderer/output_param/ansi_output_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class OutputExecutor
	{
	public:
		explicit OutputExecutor();

		bool Apply(OutputParam * param);

	private:
		StateChecker<bool> m_isEnableBlend;
		StateChecker<unsigned> m_frameBufferId;
		StateChecker<BlendFactor> m_srcFactor;
		StateChecker<BlendFactor> m_dstFactor;
		StateChecker<BlendFactor> m_srcAlphaFactor;
		StateChecker<BlendFactor> m_dstAlphaFactor;
		StateChecker<BlendOp> m_colorOp;
		StateChecker<BlendOp> m_alphaOp;

	};

}
