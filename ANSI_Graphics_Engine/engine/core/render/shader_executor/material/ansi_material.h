#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class ShaderExecutor;
	class Renderer;
	class Shader;
	class Transform;

	class Material
	{
	public:
		friend ShaderExecutor;
		friend Renderer;

		explicit Material(Shader * shader);

		virtual bool OnUpdateUniforms() = 0;

	protected:
		/* === Uniform === */
		bool SetUniform1i(const std::string & name, int value);
		bool SetUniform1iv(const std::string & name, int count, int * startAddress);
		bool SetUniform1f(const std::string & name, float value);
		bool SetUniform1fv(const std::string & name, int count, float * startAddress);
		bool SetUniform2i(const std::string & name, const glm::ivec2 & value);
		bool SetUniform2iv(const std::string & name, int count, int * startAddress);
		bool SetUniform2f(const std::string & name, const glm::vec2 & value);
		bool SetUniform2fv(const std::string & name, int count, float * startAddress);
		bool SetUniform3i(const std::string & name, const glm::ivec3 & value);
		bool SetUniform3iv(const std::string & name, int count, int * startAddress);
		bool SetUniform3f(const std::string & name, const glm::vec3 & value);
		bool SetUniform3fv(const std::string & name, int count, float * startAddress);
		bool SetUniform4i(const std::string & name, const glm::ivec4 & value);
		bool SetUniform4iv(const std::string & name, int count, int * startAddress);
		bool SetUniform4f(const std::string & name, const glm::vec4 & value);
		bool SetUniform4fv(const std::string & name, int count, float * startAddress);
		bool SetUniform4x4f(const std::string & name, const glm::mat4 & value);
		bool SetUniform4x4fv(const std::string & name, int count, float * startAddress);

	protected:
		/* === Object === */
		Transform * m_transform;

		/* === Shader === */
		unsigned m_shaderId;
		std::array<unsigned, MaximumTextureCount> m_textureIds;
		RenderType m_renderType;
		float m_specularIntensity;
		float m_specularPower;
		glm::vec4 m_diffuseColor;

		/* === Alpha === */
		bool m_isEnableAlphaTest;
		bool m_isEnableAlphaToCoverage;
		float m_alphaRef;
		CompareFunc m_alphaFunc;

		/* === Depth === */
		bool m_isEnableDepthTest;
		bool m_isEnableDepthWrite;
		CompareFunc m_depthFunc;

		/* === Stencil === */
		bool m_isEnableStencilTest;
		bool m_isEnableStencilWrite;
		int m_stencilRef;
		unsigned m_stencilMask;
		CompareFunc m_stencilFunc;
		StencilOp m_stencilFailOp;
		StencilOp m_stencilDepthFailOp;
		StencilOp m_stencilPassOp;

		/* === Raster === */
		FillMode m_fillMode;
		CullMode m_cullMode;
		FrontFace m_frontFace;

		/* === Blend === */
		bool m_isEnableBlend;
		BlendFactor m_srcFactor;
		BlendFactor m_dstFactor;
		BlendFactor m_srcAlphaFactor;
		BlendFactor m_dstAlphaFactor;
		BlendOp m_colorOp;
		BlendOp m_alphaOp;

		/* === Misc === */
		bool m_isEnableDithering;

	private:
		int GetUniformLocation(const std::string & name);

	private:
		/* === Shader === */
		static const float m_DefaultSpecularIntensity;
		static const float m_DefaultSpecularPower;
		static const glm::vec4 m_DefaultDiffuseColor;

		/* === Alpha === */
		static const bool m_DefaultIsEnableAlphaTest;
		static const bool m_DefaultIsEnableAlphaToCoverage;
		static const float m_DefaultAlphaRef;
		static const CompareFunc m_DefaultAlphaFunc;

		/* === Depth === */
		static const bool m_DefaultIsEnableDepthTest;
		static const bool m_DefaultIsEnableDepthWrite;
		static const CompareFunc m_DefaultDepthFunc;

		/* === Stencil === */
		static const bool m_DefaultIsEnableStencilTest;
		static const bool m_DefaultIsEnableStencilWrite;
		static const int m_DefaultStencilRef;
		static const unsigned m_DefaultStencilMask;
		static const CompareFunc m_DefaultStencilFunc;
		static const StencilOp m_DefaultStencilFailOp;
		static const StencilOp m_DefaultStencilDepthFailOp;
		static const StencilOp m_DefaultStencilPassOp;

		/* === Raster === */
		static const FillMode m_DefaultFillMode;
		static const CullMode m_DefaultCullMode;
		static const FrontFace m_DefaultFrontFace;

		/* === Blend === */
		static const bool m_DefaultIsEnableBlend;
		static const BlendFactor m_DefaultSrcFactor;
		static const BlendFactor m_DefaultDstFactor;
		static const BlendFactor m_DefaultSrcAlphaFactor;
		static const BlendFactor m_DefaultDstAlphaFactor;
		static const BlendOp m_DefaultColorOp;
		static const BlendOp m_DefaultAlphaOp;

		/* === Misc === */
		static const bool m_DefaultIsEnableDithering;

	private:
		std::unordered_map<std::string, int> m_uniformLocationCache;

	};

}
