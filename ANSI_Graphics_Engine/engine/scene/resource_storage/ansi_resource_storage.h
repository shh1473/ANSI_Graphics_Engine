#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class Shader;
	class Geometry;
	class Texture;

	class ResourceStorage
	{
	public:
		explicit ResourceStorage();
		~ResourceStorage();

		Shader * CreateShader(const std::string & filePath, RenderType type);
		Geometry * CreateGeometry();
		Texture * CreateTexture(const std::string & filePath);

	private:
		std::vector<Shader *> m_shaders;
		std::vector<Geometry *> m_geometries;
		std::vector<Texture *> m_textures;

	};

}
