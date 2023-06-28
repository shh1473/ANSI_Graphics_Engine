#include "ansi_shader_param.h"

#include "core/log/ansi_log.h"
#include "resource/shader/ansi_shader.h"

namespace AN
{

	ShaderParam::ShaderParam(Shader * shader) :
		m_shader(shader),
		m_uniformLocationCache()
	{

	}

	bool ShaderParam::SetUniform1i(const std::string & name, int value)
	{
		GL_CHECK(glUniform1i(GetUniformLocation(name), value));
		return true;
	}

	bool ShaderParam::SetUniform1f(const std::string & name, float value)
	{
		GL_CHECK(glUniform1f(GetUniformLocation(name), value));
		return true;
	}

	bool ShaderParam::SetUniform2f(const std::string & name, const glm::vec2 & value)
	{
		GL_CHECK(glUniform2f(GetUniformLocation(name), value.x, value.y));
		return true;
	}

	bool ShaderParam::SetUniform3f(const std::string & name, const glm::vec3 & value)
	{
		GL_CHECK(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
		return true;
	}

	bool ShaderParam::SetUniform4f(const std::string & name, const glm::vec4 & value)
	{
		GL_CHECK(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
		return true;
	}

	bool ShaderParam::SetUniform4x4f(const std::string & name, const glm::mat4 & value)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
		return true;
	}

	int ShaderParam::GetUniformLocation(const std::string & name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) { return m_uniformLocationCache[name]; }

		int location = glGetUniformLocation(m_shader->GetId(), name.c_str());
		AN_ERROR_LOG_IF(location != -1);

		m_uniformLocationCache[name] = location;
		return location;
	}

}
