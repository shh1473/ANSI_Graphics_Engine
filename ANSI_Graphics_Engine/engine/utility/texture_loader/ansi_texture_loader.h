#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class TextureLoader
	{
	public:
		static bool Load(const std::string & filePath, int & width, int & height, unsigned & textureId);

	private:
		explicit TextureLoader() = delete;

	};

}
