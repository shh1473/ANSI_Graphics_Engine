#pragma once

#include "common/ansi_common.h"

namespace AN
{

	enum class FillMode {
		Point = GL_POINT,
		Line = GL_LINE,
		Fill = GL_FILL,
	};
	enum class CullMode {
		None,
		Front = GL_FRONT,
		Back = GL_BACK,
		FrontAndBack = GL_FRONT_AND_BACK,
	};
	enum class FrontFace {
		CW = GL_CW,
		CCW = GL_CCW,
	};
	enum class MSAA
	{
		None,
		Nicest = GL_NICEST,
		Fastest = GL_FASTEST,
		DontCare = GL_DONT_CARE,
	};

	class RasterExecutor;

	class RasterParam
	{
	public:
		friend class RasterExecutor;

		explicit RasterParam();

		void SetFillMode(FillMode fillMode) { m_fillMode = fillMode; }
		void SetCullMode(CullMode cullMode) { m_cullMode = cullMode; }
		void SetFrontFace(FrontFace frontFace) {m_frontFace = frontFace; }
		void SetMSAA(MSAA msaa) { m_msaa = msaa; }
		void SetDepthClipNear(double depthClipNear) { m_depthClipNear = depthClipNear; }
		void SetDepthClipFar(double depthClipFar) { m_depthClipFar = depthClipFar; }

	private:
		static const FillMode m_DefaultFillMode;
		static const CullMode m_DefaultCullMode;
		static const FrontFace m_DefaultFrontFace;
		static const MSAA m_DefaultMSAA;
		static const double m_DefaultDepthClipNear;
		static const double m_DefaultDepthClipFar;

		FillMode m_fillMode;
		CullMode m_cullMode;
		FrontFace m_frontFace;
		MSAA m_msaa;
		double m_depthClipNear;
		double m_depthClipFar;

	};

}
