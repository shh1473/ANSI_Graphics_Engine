#pragma once

#include "resource/shader/ansi_shader.h"

namespace AN
{

	class ResourceStorage
	{
	public:
		explicit ResourceStorage();
		~ResourceStorage();

		Shader * CreateShader(const std::string & filePath);

	private:
		std::vector<Shader *> m_shaders;

	};

}
