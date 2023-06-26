#pragma once

#include "common/ansi_common.h"

namespace AN
{

	using Uniform1iPair = std::pair<const std::string, int &>;
	using Uniform1fPair = std::pair<const std::string, float &>;
	using Uniform2fPair = std::pair<const std::string, glm::vec2 &>;
	using Uniform3fPair = std::pair<const std::string, glm::vec3 &>;
	using Uniform4fPair = std::pair<const std::string, glm::vec4 &>;
	using Uniform4fvPair = std::pair<const std::string, glm::mat4 &>;

	class ShaderExecutor;

	class ShaderParam
	{
	public:
		friend ShaderExecutor;

		explicit ShaderParam();

		void SetUniform1i(const std::string & name, int & value);
		void SetUniform1f(const std::string & name, float & value);
		void SetUniform2f(const std::string & name, glm::vec2 & value);
		void SetUniform3f(const std::string & name, glm::vec3 & value);
		void SetUniform4f(const std::string & name, glm::vec4 & value);
		void SetUniform4fv(const std::string & name, glm::mat4 & value);

	private:
		int GetUniformLocation(const std::string & name);

		unsigned m_shaderId;
		std::vector<Uniform1iPair> m_uniforms1i;
		std::vector<Uniform1fPair> m_uniforms1f;
		std::vector<Uniform2fPair> m_uniforms2f;
		std::vector<Uniform3fPair> m_uniforms3f;
		std::vector<Uniform4fPair> m_uniforms4f;
		std::vector<Uniform4fvPair> m_uniforms4fv;
		std::unordered_map<std::string, int> m_uniformLocationCache;

	};

}
