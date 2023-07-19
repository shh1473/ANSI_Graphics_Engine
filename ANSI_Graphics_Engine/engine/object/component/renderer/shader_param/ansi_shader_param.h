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
		bool SetUniform1f(const std::string & name, float value);
		bool SetUniform2f(const std::string & name, const glm::vec2 & value);
		bool SetUniform3f(const std::string & name, const glm::vec3 & value);
		bool SetUniform4f(const std::string & name, const glm::vec4 & value);
		bool SetUniform4x4f(const std::string & name, const glm::mat4 & value);

		void SetTexture(unsigned slotIndex, unsigned textureId) { m_textureIds[slotIndex] = textureId; }

	private:
		int GetUniformLocation(const std::string & name);

		Shader * m_shader;
		std::array<unsigned, MaximumTextureCount> m_textureIds;
		std::unordered_map<std::string, int> m_uniformLocationCache;

	};

}
