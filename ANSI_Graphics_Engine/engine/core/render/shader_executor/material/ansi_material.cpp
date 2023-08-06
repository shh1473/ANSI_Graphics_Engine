#include "ansi_material.h"

#include "core/log/ansi_log.h"
#include "resource/shader/ansi_shader.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	/* === Shader === */
	const float Material::m_DefaultSpecularIntensity{ 1.0f };
	const float Material::m_DefaultSpecularPower{ 32.0f };
	const glm::vec4 Material::m_DefaultDiffuseColor{ 1.0f };

	/* === Alpha === */
	const bool Material::m_DefaultIsEnableAlphaTest{ false };
	const bool Material::m_DefaultIsEnableAlphaToCoverage{ false };
	const float Material::m_DefaultAlphaRef{ 0.0f };
	const CompareFunc Material::m_DefaultAlphaFunc{ CompareFunc::GreaterEqual };

	/* === Depth === */
	const bool Material::m_DefaultIsEnableDepthTest{ true };
	const bool Material::m_DefaultIsEnableDepthWrite{ true };
	const CompareFunc Material::m_DefaultDepthFunc{ CompareFunc::LessEqual };

	/* === Stencil === */
	const bool Material::m_DefaultIsEnableStencilTest{ false };
	const bool Material::m_DefaultIsEnableStencilWrite{ false };
	const int Material::m_DefaultStencilRef{ 0 };
	const unsigned Material::m_DefaultStencilMask{ 0xff };
	const CompareFunc Material::m_DefaultStencilFunc{ CompareFunc::Always };
	const StencilOp Material::m_DefaultStencilFailOp{ StencilOp::Keep };
	const StencilOp Material::m_DefaultStencilDepthFailOp{ StencilOp::Keep };
	const StencilOp Material::m_DefaultStencilPassOp{ StencilOp::Keep };

	/* === Raster === */
	const FillMode Material::m_DefaultFillMode{ FillMode::Solid };
	const CullMode Material::m_DefaultCullMode{ CullMode::Back };
	const FrontFace Material::m_DefaultFrontFace{ FrontFace::CCW };

	/* === Blend === */
	const bool Material::m_DefaultIsEnableBlend{ false };
	const BlendFactor Material::m_DefaultSrcFactor{ BlendFactor::One };
	const BlendFactor Material::m_DefaultDstFactor{ BlendFactor::Zero };
	const BlendFactor Material::m_DefaultSrcAlphaFactor{ BlendFactor::One };
	const BlendFactor Material::m_DefaultDstAlphaFactor{ BlendFactor::Zero };
	const BlendOp Material::m_DefaultColorOp{ BlendOp::Add };
	const BlendOp Material::m_DefaultAlphaOp{ BlendOp::Add };

	/* === Misc === */
	const bool Material::m_DefaultIsEnableDithering{ false };

	Material::Material(Shader * shader) :
		/* === Object === */
		m_transform(nullptr),
		/* === Shader === */
		m_shaderId(shader->GetId()),
		m_renderType(shader->GetType()),
		m_textureIds(),
		m_textureTypes(),
		m_specularIntensity(m_DefaultSpecularIntensity),
		m_specularPower(m_DefaultSpecularPower),
		m_diffuseColor(m_DefaultDiffuseColor),
		m_uniformLocationCache(),
		/* === Alpha === */
		m_isEnableAlphaTest(m_DefaultIsEnableAlphaTest),
		m_isEnableAlphaToCoverage(m_DefaultIsEnableAlphaToCoverage),
		m_alphaRef(m_DefaultAlphaRef),
		m_alphaFunc(m_DefaultAlphaFunc),
		/* === Depth === */
		m_isEnableDepthTest(m_DefaultIsEnableDepthTest),
		m_isEnableDepthWrite(m_DefaultIsEnableDepthWrite),
		m_depthFunc(m_DefaultDepthFunc),
		/* === Stencil === */
		m_isEnableStencilTest(m_DefaultIsEnableStencilTest),
		m_isEnableStencilWrite(m_DefaultIsEnableStencilWrite),
		m_stencilRef(m_DefaultStencilRef),
		m_stencilMask(m_DefaultStencilMask),
		m_stencilFunc(m_DefaultStencilFunc),
		m_stencilFailOp(m_DefaultStencilFailOp),
		m_stencilDepthFailOp(m_DefaultStencilDepthFailOp),
		m_stencilPassOp(m_DefaultStencilPassOp),
		/* === Raster === */
		m_fillMode(m_DefaultFillMode),
		m_cullMode(m_DefaultCullMode),
		m_frontFace(m_DefaultFrontFace),
		/* === Blend === */
		m_isEnableBlend(m_DefaultIsEnableBlend),
		m_srcFactor(m_DefaultSrcFactor),
		m_dstFactor(m_DefaultDstFactor),
		m_srcAlphaFactor(m_DefaultSrcAlphaFactor),
		m_dstAlphaFactor(m_DefaultDstAlphaFactor),
		m_colorOp(m_DefaultColorOp),
		m_alphaOp(m_DefaultAlphaOp),
		/* === Misc === */
		m_isEnableDithering(m_DefaultIsEnableDithering)
	{
		m_textureTypes.fill(TextureType::Two);
	}

	bool Material::SetUniform1i(const std::string & name, int value)
	{
		GL_CHECK(glUniform1iv(GetUniformLocation(name), 1, &value));
		return true;
	}

	bool Material::SetUniform1iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform1iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform1f(const std::string & name, float value)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), 1, &value));
		return true;
	}

	bool Material::SetUniform1fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform2i(const std::string & name, const glm::ivec2 & value)
	{
		GL_CHECK(glUniform2iv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool Material::SetUniform2iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform2iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform2f(const std::string & name, const glm::vec2 & value)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool Material::SetUniform2fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform3i(const std::string & name, const glm::ivec3 & value)
	{
		GL_CHECK(glUniform3iv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool Material::SetUniform3iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform3iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform3f(const std::string & name, const glm::vec3 & value)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool Material::SetUniform3fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform4i(const std::string & name, const glm::ivec4 & value)
	{
		GL_CHECK(glUniform4iv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool Material::SetUniform4iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform4iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform4f(const std::string & name, const glm::vec4 & value)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool Material::SetUniform4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool Material::SetUniform4x4f(const std::string & name, const glm::mat4 & value)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
		return true;
	}

	bool Material::SetUniform4x4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, startAddress));
		return true;
	}

	int Material::GetUniformLocation(const std::string & name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) { return m_uniformLocationCache[name]; }

		int location = glGetUniformLocation(m_shaderId, name.c_str());
		AN_ERROR_LOG_IF_M(location != -1, Converter::ToUnicode(name));

		m_uniformLocationCache[name] = location;
		return location;
	}

}
