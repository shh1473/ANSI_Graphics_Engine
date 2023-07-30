#pragma once

#include "common/ansi_common_render.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class Material;

	class ShaderExecutor
	{
	public:
		explicit ShaderExecutor();

		bool Apply(Material * material);
		void Reset();

	private:
		bool ApplyShader();
		bool ApplyAlpha();
		bool ApplyDepth();
		bool ApplyStencil();
		bool ApplyRaster();
		bool ApplyBlend();
		bool ApplyMisc();

	private:
		StateChecker<Material *> m_material;
		StateChecker<unsigned> m_shaderId;
		StateArrayChecker<unsigned, MaximumTextureCount> m_textureIds;

		/* === Alpha === */
		StateChecker<bool> m_isEnableAlphaTest;
		StateChecker<bool> m_isEnableAlphaToCoverage;
		StateChecker<float> m_alphaRef;
		StateChecker<CompareFunc> m_alphaFunc;

		/* === Depth === */
		StateChecker<bool> m_isEnableDepthTest;
		StateChecker<bool> m_isEnableDepthWrite;
		StateChecker<CompareFunc> m_depthFunc;

		/* === Stencil === */
		StateChecker<bool> m_isEnableStencilTest;
		StateChecker<bool> m_isEnableStencilWrite;
		StateChecker<int> m_stencilRef;
		StateChecker<unsigned> m_stencilMask;
		StateChecker<CompareFunc> m_stencilFunc;
		StateChecker<StencilOp> m_stencilFailOp;
		StateChecker<StencilOp> m_stencilDepthFailOp;
		StateChecker<StencilOp> m_stencilPassOp;

		/* === Raster === */
		StateChecker<FillMode> m_fillMode;
		StateChecker<CullMode> m_cullMode;
		StateChecker<CullMode> m_shadowCullMode;
		StateChecker<FrontFace> m_frontFace;

		/* === Blend === */
		StateChecker<bool> m_isEnableBlend;
		StateChecker<BlendFactor> m_srcFactor;
		StateChecker<BlendFactor> m_dstFactor;
		StateChecker<BlendFactor> m_srcAlphaFactor;
		StateChecker<BlendFactor> m_dstAlphaFactor;
		StateChecker<BlendOp> m_colorOp;
		StateChecker<BlendOp> m_alphaOp;

		/* === Misc === */
		StateChecker<bool> m_isEnableDithering;

	};

}
