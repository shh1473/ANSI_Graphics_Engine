#pragma once

#include "common/ansi_common.h"

namespace AN
{

	enum class BlendFactor
	{
		One = GL_ONE,
		Zero = GL_ZERO,
		SrcColor = GL_SRC_COLOR,
		DstColor = GL_DST_COLOR,
		SrcAlpha = GL_SRC_ALPHA,
		DstAlpha = GL_DST_ALPHA,
		InvSrcColor = GL_ONE_MINUS_SRC_COLOR,
		InvDstColor = GL_ONE_MINUS_DST_COLOR,
		InvSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
		InvDstAlpha = GL_ONE_MINUS_DST_ALPHA,
	};
	enum class BlendOp
	{
		Add = GL_FUNC_ADD,
		Subtract = GL_FUNC_SUBTRACT,
		ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
		Min = GL_MIN,
		Max = GL_MAX,
	};

	class OutputExecutor;

	class OutputParam
	{
	public:
		friend class OutputExecutor;

		explicit OutputParam();

		void SetIsEnableBlend(bool isEnableBlend) { m_isEnableBlend = isEnableBlend; }
		void SetFrameBufferId(unsigned frameBufferId) { m_frameBufferId = frameBufferId; }
		void SetSrcFactor(BlendFactor srcFactor) { m_srcFactor = srcFactor; }
		void SetDstFactor(BlendFactor dstFactor) { m_dstFactor = dstFactor; }
		void SetSrcAlphaFactor(BlendFactor srcAlphaFactor) { m_srcAlphaFactor = srcAlphaFactor; }
		void SetDstAlphaFactor(BlendFactor dstAlphaFactor) { m_dstAlphaFactor = dstAlphaFactor; }
		void SetColorOp(BlendOp colorOp) { m_colorOp = colorOp; }
		void SetAlphaOp(BlendOp alphaOp) { m_alphaOp = alphaOp; }

	private:
		static const bool m_DefaultIsEnableBlend;
		static const unsigned m_DefaultFrameBufferId;
		static const BlendFactor m_DefaultSrcFactor;
		static const BlendFactor m_DefaultDstFactor;
		static const BlendFactor m_DefaultSrcAlphaFactor;
		static const BlendFactor m_DefaultDstAlphaFactor;
		static const BlendOp m_DefaultColorOp;
		static const BlendOp m_DefaultAlphaOp;

		bool m_isEnableBlend;
		unsigned m_frameBufferId;
		BlendFactor m_srcFactor;
		BlendFactor m_dstFactor;
		BlendFactor m_srcAlphaFactor;
		BlendFactor m_dstAlphaFactor;
		BlendOp m_colorOp;
		BlendOp m_alphaOp;

	};

}
