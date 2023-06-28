#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Shader;
	class ShaderExecutor;

	class ShaderParam
	{
	public:
		friend ShaderExecutor;

		explicit ShaderParam(Shader * shader);

		virtual bool OnRender() = 0;

		Shader * GetShader() const { return m_shader; }

	protected:
		bool SetUniform1i(const std::string & name, int value);
		bool SetUniform1f(const std::string & name, float value);
		bool SetUniform2f(const std::string & name, const glm::vec2 & value);
		bool SetUniform3f(const std::string & name, const glm::vec3 & value);
		bool SetUniform4f(const std::string & name, const glm::vec4 & value);
		bool SetUniform4x4f(const std::string & name, const glm::mat4 & value);

	private:
		int GetUniformLocation(const std::string & name);

		Shader * m_shader;
		std::unordered_map<std::string, int> m_uniformLocationCache;

	};

}
