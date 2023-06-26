#include "ansi_raster_param.h"

namespace AN
{

	FillMode const RasterParam::m_DefaultFillMode{ FillMode::Fill };
	CullMode const RasterParam::m_DefaultCullMode{ CullMode::Back };
	FrontFace const RasterParam::m_DefaultFrontFace{ FrontFace::CCW };
	MSAA const RasterParam::m_DefaultMSAA{ MSAA::None };
	double const RasterParam::m_DefaultDepthClipNear{ 0.0 };
	double const RasterParam::m_DefaultDepthClipFar{ 1.0 };

	RasterParam::RasterParam() :
		m_fillMode(m_DefaultFillMode),
		m_cullMode(m_DefaultCullMode),
		m_frontFace(m_DefaultFrontFace),
		m_msaa(m_DefaultMSAA),
		m_depthClipNear(m_DefaultDepthClipNear),
		m_depthClipFar(m_DefaultDepthClipFar)
	{

	}

}
