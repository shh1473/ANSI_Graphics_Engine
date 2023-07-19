#include "ansi_texture_loader.h"

#include "stb/stb_image.h"
#include "core/log/ansi_log.h"

namespace AN
{

	bool TextureLoader::Load(const std::string & filePath, int & width, int & height, unsigned & textureId)
	{
		int bitsPerPixel;

		stbi_set_flip_vertically_on_load(1);
		auto localBuffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4);
		AN_CHECK_LOG(localBuffer);

		GL_CHECK(glGenTextures(1, &textureId));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));

		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

		stbi_image_free(localBuffer);

		return true;
	}

}
