#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class ShaderExecutor;
	class Shader;

	class ShaderParam
	{
	public:
		friend ShaderExecutor;

		explicit ShaderParam(Shader * shader);

		virtual bool OnUpdateUniforms() = 0;

		Shader * GetShader() const { return m_shader; }

	protected:
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

		void SetTexture(unsigned slotIndex, unsigned textureId) { m_textureIds[slotIndex] = textureId; }

	private:
		int GetUniformLocation(const std::string & name);

		Shader * m_shader;
		std::array<unsigned, MaximumTextureCount> m_textureIds;
		std::unordered_map<std::string, int> m_uniformLocationCache;

	};

}
