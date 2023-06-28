#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class Shader;
	class Geometry;

	class ResourceStorage
	{
	public:
		explicit ResourceStorage();
		~ResourceStorage();

		Shader * CreateShader(const std::string & filePath, RenderType type);
		Geometry * CreateGeometry();

	private:
		std::vector<Shader *> m_shaders;
		std::vector<Geometry *> m_geometries;

	};

}
