#include "ansi_resource_storage.h"

#include "utility/shader_loader/ansi_shader_loader.h"

namespace AN
{

	ResourceStorage::ResourceStorage()
	{

	}

	ResourceStorage::~ResourceStorage()
	{
		for (auto iter = m_shaders.begin(); iter != m_shaders.end(); ++iter)
		{
			AN_DELETE(*iter);
		}
	}

	Shader * ResourceStorage::CreateShader(const std::string & filePath)
	{
		unsigned shaderId{ 0 };
		if (!ShaderLoader::LoadShader(filePath, shaderId)) { return nullptr; }
		return new Shader(shaderId);
	}

}
