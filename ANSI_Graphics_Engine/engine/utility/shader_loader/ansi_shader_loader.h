#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class ShaderLoader
	{
	public:
		static bool LoadShader(const std::string & filePath, unsigned & resourceId);

	private:
		explicit ShaderLoader() = delete;

		static bool ParseShader(const std::string & filePath, std::string & vsSource, std::string & fsSource);
		static bool CompileShader(unsigned type, const std::string & source, unsigned & shaderId);

	};

}
