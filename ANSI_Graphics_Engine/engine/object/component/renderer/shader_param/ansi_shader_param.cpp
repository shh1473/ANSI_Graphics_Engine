#include "ansi_shader_param.h"

#include "core/log/ansi_log.h"
#include "resource/shader/ansi_shader.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	ShaderParam::ShaderParam(Shader * shader) :
		m_shader(shader),
		m_textureIds(),
		m_uniformLocationCache()
	{

	}

	bool ShaderParam::SetUniform1i(const std::string & name, int value)
	{
		GL_CHECK(glUniform1iv(GetUniformLocation(name), 1, &value));
		return true;
	}

	bool ShaderParam::SetUniform1iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform1iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform1f(const std::string & name, float value)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), 1, &value));
		return true;
	}

	bool ShaderParam::SetUniform1fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform2i(const std::string & name, const glm::ivec2 & value)
	{
		GL_CHECK(glUniform2iv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool ShaderParam::SetUniform2iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform2iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform2f(const std::string & name, const glm::vec2 & value)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool ShaderParam::SetUniform2fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform3i(const std::string & name, const glm::ivec3 & value)
	{
		GL_CHECK(glUniform3iv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool ShaderParam::SetUniform3iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform3iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform3f(const std::string & name, const glm::vec3 & value)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool ShaderParam::SetUniform3fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform4i(const std::string & name, const glm::ivec4 & value)
	{
		GL_CHECK(glUniform4iv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool ShaderParam::SetUniform4iv(const std::string & name, int count, int * startAddress)
	{
		GL_CHECK(glUniform4iv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform4f(const std::string & name, const glm::vec4 & value)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	bool ShaderParam::SetUniform4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	bool ShaderParam::SetUniform4x4f(const std::string & name, const glm::mat4 & value)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
		return true;
	}

	bool ShaderParam::SetUniform4x4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, startAddress));
		return true;
	}

	int ShaderParam::GetUniformLocation(const std::string & name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) { return m_uniformLocationCache[name]; }

		int location = glGetUniformLocation(m_shader->GetId(), name.c_str());
		AN_ERROR_LOG_IF_M(location != -1, Converter::ToUnicode(name));

		m_uniformLocationCache[name] = location;
		return location;
	}

}
