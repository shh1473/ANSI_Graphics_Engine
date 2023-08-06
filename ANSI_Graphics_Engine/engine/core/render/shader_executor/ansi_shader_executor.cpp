#include "ansi_shader_executor.h"

#include "material/ansi_material.h"
#include "resource/shader/ansi_shader.h"
#include "resource/texture/ansi_texture.h"

namespace AN
{

	ShaderExecutor::ShaderExecutor()
	{
		Reset();
	}

	bool ShaderExecutor::Apply(Material * material)
	{
		/* === Shader === */
		m_shaderId.Set(material->m_shaderId);
		for (unsigned i{ 0 }; i < MaximumTextureCount; ++i) {
			m_textureIds.Set(i, material->m_textureIds[i]);
			m_textureTypes.Set(i, static_cast<unsigned>(material->m_textureTypes[i]));
		}

		/* === Alpha === */
		m_isEnableAlphaTest.Set(material->m_isEnableAlphaTest);
		m_isEnableAlphaToCoverage.Set(material->m_isEnableAlphaToCoverage);
		m_alphaRef.Set(material->m_alphaRef);
		m_alphaFunc.Set(material->m_alphaFunc);

		/* === Depth === */
		m_isEnableDepthWrite = material->m_isEnableDepthWrite;
		m_isEnableDepthTest.Set(material->m_isEnableDepthTest);
		m_depthFunc.Set(material->m_depthFunc);

		/* === Stencil === */
		m_isEnableStencilTest.Set(material->m_isEnableStencilTest);
		m_isEnableStencilWrite.Set(material->m_isEnableStencilWrite);
		m_stencilRef.Set(material->m_stencilRef);
		m_stencilMask.Set(material->m_stencilMask);
		m_stencilFunc.Set(material->m_stencilFunc);
		m_stencilFailOp.Set(material->m_stencilFailOp);
		m_stencilDepthFailOp.Set(material->m_stencilDepthFailOp);
		m_stencilPassOp.Set(material->m_stencilPassOp);

		/* === Raster === */
		m_fillMode.Set(material->m_fillMode);
		m_cullMode.Set(material->m_cullMode);
		m_frontFace.Set(material->m_frontFace);

		/* === Blend === */
		m_isEnableBlend.Set(material->m_isEnableBlend);
		m_srcFactor.Set(material->m_srcFactor);
		m_dstFactor.Set(material->m_dstFactor);
		m_srcAlphaFactor.Set(material->m_srcAlphaFactor);
		m_dstAlphaFactor.Set(material->m_dstAlphaFactor);
		m_colorOp.Set(material->m_colorOp);
		m_alphaOp.Set(material->m_alphaOp);

		/* === Misc === */
		m_isEnableDithering.Set(material->m_isEnableDithering);

		AN_CHECK(ApplyShader());
		AN_CHECK(ApplyAlpha());
		AN_CHECK(ApplyDepth());
		AN_CHECK(ApplyStencil());
		AN_CHECK(ApplyRaster());
		AN_CHECK(ApplyBlend());
		AN_CHECK(ApplyMisc());

		AN_CHECK(material->OnUpdateUniforms());

		return true;
	}

	void ShaderExecutor::Reset()
	{
		m_material.Set(nullptr);
		m_material.Reset();

		/* === Shader === */
		m_shaderId.Set(0);
		m_textureIds.SetAll(0);
		m_textureTypes.SetAll(static_cast<unsigned>(TextureType::Two));
		m_shaderId.Reset();
		m_textureIds.Reset();
		m_textureTypes.Reset();

		/* === Alpha === */
		m_isEnableAlphaTest.Set(Material::m_DefaultIsEnableAlphaTest);
		m_isEnableAlphaToCoverage.Set(Material::m_DefaultIsEnableAlphaToCoverage);
		m_alphaRef.Set(Material::m_DefaultAlphaRef);
		m_alphaFunc.Set(Material::m_DefaultAlphaFunc);
		m_isEnableAlphaTest.Reset();
		m_isEnableAlphaToCoverage.Reset();
		m_alphaRef.Reset();
		m_alphaFunc.Reset();

		/* === Depth === */
		m_isEnableDepthWrite = Material::m_DefaultIsEnableDepthWrite;
		m_isEnableDepthTest.Set(Material::m_DefaultIsEnableDepthTest);
		m_depthFunc.Set(Material::m_DefaultDepthFunc);
		m_isEnableDepthTest.Reset();
		m_depthFunc.Reset();

		/* === Stencil === */
		m_isEnableStencilTest.Set(Material::m_DefaultIsEnableStencilTest);
		m_isEnableStencilWrite.Set(Material::m_DefaultIsEnableStencilWrite);
		m_stencilFunc.Set(Material::m_DefaultStencilFunc);
		m_stencilRef.Set(Material::m_DefaultStencilRef);
		m_stencilMask.Set(Material::m_DefaultStencilMask);
		m_stencilFailOp.Set(Material::m_DefaultStencilFailOp);
		m_stencilDepthFailOp.Set(Material::m_DefaultStencilDepthFailOp);
		m_stencilPassOp.Set(Material::m_DefaultStencilPassOp);
		m_isEnableStencilTest.Reset();
		m_isEnableStencilWrite.Reset();
		m_stencilFunc.Reset();
		m_stencilRef.Reset();
		m_stencilMask.Reset();
		m_stencilFailOp.Reset();
		m_stencilDepthFailOp.Reset();
		m_stencilPassOp.Reset();

		/* === Raster === */
		m_fillMode.Set(Material::m_DefaultFillMode);
		m_cullMode.Set(Material::m_DefaultCullMode);
		m_frontFace.Set(Material::m_DefaultFrontFace);
		m_fillMode.Reset();
		m_cullMode.Reset();
		m_shadowCullMode.Reset();
		m_frontFace.Reset();

		/* === Blend === */
		m_isEnableBlend.Set(Material::m_DefaultIsEnableBlend);
		m_srcFactor.Set(Material::m_DefaultSrcFactor);
		m_dstFactor.Set(Material::m_DefaultDstFactor);
		m_srcAlphaFactor.Set(Material::m_DefaultSrcAlphaFactor);
		m_dstAlphaFactor.Set(Material::m_DefaultDstAlphaFactor);
		m_colorOp.Set(Material::m_DefaultColorOp);
		m_alphaOp.Set(Material::m_DefaultAlphaOp);
		m_isEnableBlend.Reset();
		m_srcFactor.Reset();
		m_dstFactor.Reset();
		m_srcAlphaFactor.Reset();
		m_dstAlphaFactor.Reset();
		m_colorOp.Reset();
		m_alphaOp.Reset();

		/* === Misc === */
		m_isEnableDithering.Set(Material::m_DefaultIsEnableDithering);
		m_isEnableDithering.Reset();
	}

	bool ShaderExecutor::ApplyShader()
	{
		if (m_shaderId.Check())
		{
			m_shaderId.Reset();
			GL_CHECK(glUseProgram(m_shaderId.Get()));
		}

		if (m_textureIds.Check() || m_textureTypes.Check())
		{
			for (int i{ m_textureIds.GetStart() }; i <= m_textureIds.GetEnd(); ++i)
			{
				GL_CHECK(glActiveTexture(GL_TEXTURE0 + i));
				GL_CHECK(glBindTexture(m_textureTypes.Get(i), m_textureIds.Get(i)));
			}
			m_textureIds.Reset();
			m_textureTypes.Reset();
		}

		return true;
	}

	bool ShaderExecutor::ApplyAlpha()
	{
		if (m_isEnableAlphaTest.Check())
		{
			m_isEnableAlphaTest.Reset();
			if (m_isEnableAlphaTest.Get()) { GL_CHECK(glEnable(GL_ALPHA_TEST)); }
			else { GL_CHECK(glDisable(GL_ALPHA_TEST)); }
		}

		if (m_isEnableAlphaToCoverage.Check())
		{
			m_isEnableAlphaToCoverage.Reset();
			if (m_isEnableAlphaToCoverage.Get()) { GL_CHECK(glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE)); }
			else { GL_CHECK(glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE)); }
		}

		if (m_alphaRef.Check() || m_alphaFunc.Check())
		{
			m_alphaRef.Reset();
			m_alphaFunc.Reset();
			GL_CHECK(glAlphaFunc(static_cast<unsigned>(m_alphaFunc.Get()), m_alphaRef.Get()));
		}

		return true;
	}

	bool ShaderExecutor::ApplyDepth()
	{
		GL_CHECK(glDepthMask(m_isEnableDepthWrite ? GL_TRUE : GL_FALSE));

		if (m_isEnableDepthTest.Check())
		{
			m_isEnableDepthTest.Reset();
			if (m_isEnableDepthTest.Get()) { GL_CHECK(glEnable(GL_DEPTH_TEST)); }
			else { GL_CHECK(glDisable(GL_DEPTH_TEST)); }
		}

		if (m_depthFunc.Check())
		{
			m_depthFunc.Reset();
			GL_CHECK(glDepthFunc(static_cast<unsigned>(m_depthFunc.Get())));
		}

		return true;
	}

	bool ShaderExecutor::ApplyStencil()
	{
		if (m_isEnableStencilTest.Check())
		{
			m_isEnableStencilTest.Reset();
			if (m_isEnableStencilTest.Get()) { GL_CHECK(glEnable(GL_STENCIL_TEST)); }
			else { GL_CHECK(glDisable(GL_STENCIL_TEST)); }
		}

		if (m_isEnableStencilWrite.Check())
		{
			m_isEnableStencilWrite.Reset();
			GL_CHECK(glStencilMask(m_isEnableStencilWrite.Get() ? GL_TRUE : GL_FALSE));
		}

		if (m_stencilRef.Check() || m_stencilMask.Check() || m_stencilFunc.Check())
		{
			m_stencilRef.Reset();
			m_stencilMask.Reset();
			m_stencilFunc.Reset();
			GL_CHECK(glStencilFunc(static_cast<unsigned>(m_stencilFunc.Get()), m_stencilRef.Get(), m_stencilMask.Get()));
		}

		if (m_stencilFailOp.Check() || m_stencilDepthFailOp.Check() || m_stencilPassOp.Check())
		{
			m_stencilFailOp.Reset();
			m_stencilDepthFailOp.Reset();
			m_stencilPassOp.Reset();
			GL_CHECK(glStencilOp(
				static_cast<unsigned>(m_stencilFailOp.Get()),
				static_cast<unsigned>(m_stencilDepthFailOp.Get()),
				static_cast<unsigned>(m_stencilPassOp.Get())));
		}

		return true;
	}

	bool ShaderExecutor::ApplyRaster()
	{
		if (m_fillMode.Check())
		{
			m_fillMode.Reset();
			GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, static_cast<unsigned>(m_fillMode.Get())));
		}

		if (m_cullMode.Check())
		{
			m_cullMode.Reset();
			if (m_cullMode.Get() == CullMode::None)
			{
				GL_CHECK(glDisable(GL_CULL_FACE));
			}
			else
			{
				GL_CHECK(glEnable(GL_CULL_FACE));
				GL_CHECK(glCullFace(static_cast<unsigned>(m_cullMode.Get())));
			}
		}

		if (m_frontFace.Check())
		{
			m_frontFace.Reset();
			GL_CHECK(glFrontFace(static_cast<unsigned>(m_frontFace.Get())));
		}

		return true;
	}

	bool ShaderExecutor::ApplyBlend()
	{
		if (m_isEnableBlend.Check())
		{
			m_isEnableBlend.Reset();
			if (m_isEnableBlend.Get())
			{
				GL_CHECK(glEnable(GL_BLEND));
			}
			else
			{
				GL_CHECK(glDisable(GL_BLEND));
			}
		}

		if (m_srcFactor.Check() || m_dstFactor.Check() || m_srcAlphaFactor.Check() || m_dstAlphaFactor.Check())
		{
			m_srcFactor.Reset();
			m_dstFactor.Reset();
			m_srcAlphaFactor.Reset();
			m_dstAlphaFactor.Reset();
			GL_CHECK(glBlendFuncSeparate(
				static_cast<unsigned>(m_srcFactor.Get()),
				static_cast<unsigned>(m_dstFactor.Get()),
				static_cast<unsigned>(m_srcAlphaFactor.Get()),
				static_cast<unsigned>(m_dstAlphaFactor.Get())));
		}

		if (m_colorOp.Check() || m_alphaOp.Check())
		{
			m_colorOp.Reset();
			m_alphaOp.Reset();
			GL_CHECK(glBlendEquationSeparate(
				static_cast<unsigned>(m_colorOp.Get()),
				static_cast<unsigned>(m_alphaOp.Get())));
		}

		return true;
	}

	bool ShaderExecutor::ApplyMisc()
	{
		if (m_isEnableDithering.Check())
		{
			m_isEnableDithering.Reset();
			if (m_isEnableDithering.Get()) { GL_CHECK(glEnable(GL_DITHER)); }
			else { GL_CHECK(glDisable(GL_DITHER)); }
		}

		return true;
	}

}
