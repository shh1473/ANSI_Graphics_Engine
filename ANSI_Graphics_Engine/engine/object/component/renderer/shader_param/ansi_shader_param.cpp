#include "ansi_shader_param.h"

#include "core/ansi_core.h"
#include "core/log/ansi_log.h"

namespace AN
{

	ShaderParam::ShaderParam() :
		m_shaderId(0),
		m_uniforms1i(),
		m_uniforms1f(),
		m_uniforms2f(),
		m_uniforms3f(),
		m_uniforms4f(),
		m_uniforms4fv(),
		m_uniformLocationCache()
	{

	}

	void ShaderParam::SetUniform1i(const std::string & name, int & value)
	{
		m_uniforms1i.push_back(Uniform1iPair(name, value));
	}

	void ShaderParam::SetUniform1f(const std::string & name, float & value)
	{
		m_uniforms1f.push_back(Uniform1fPair(name, value));
	}

	void ShaderParam::SetUniform2f(const std::string & name, glm::vec2 & value)
	{
		m_uniforms2f.push_back(Uniform2fPair(name, value));
	}

	void ShaderParam::SetUniform3f(const std::string & name, glm::vec3 & value)
	{
		m_uniforms3f.push_back(Uniform3fPair(name, value));
	}

	void ShaderParam::SetUniform4f(const std::string & name, glm::vec4 & value)
	{
		m_uniforms4f.push_back(Uniform4fPair(name, value));
	}

	void ShaderParam::SetUniform4fv(const std::string & name, glm::mat4 & value)
	{
		m_uniforms4fv.push_back(Uniform4fvPair(name, value));
	}

	int ShaderParam::GetUniformLocation(const std::string & name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) { return m_uniformLocationCache[name]; }

		int location = glGetUniformLocation(m_shaderId, name.c_str());
		AN_ERROR_LOG_IF(location != -1);

		m_uniformLocationCache[name] = location;
		return location;
	}

}
