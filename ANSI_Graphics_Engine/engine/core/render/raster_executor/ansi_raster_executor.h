#pragma once

#include "object/component/camera/raster_param/ansi_raster_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class RasterExecutor
	{
	public:
		explicit RasterExecutor();

		bool Apply(RasterParam * param);

	private:
		StateChecker<FillMode> m_fillMode;
		StateChecker<CullMode> m_cullMode;
		StateChecker<FrontFace> m_frontFace;
		StateChecker<MSAA> m_msaa;
		StateChecker<double> m_depthClipNear;
		StateChecker<double> m_depthClipFar;

	};

}
