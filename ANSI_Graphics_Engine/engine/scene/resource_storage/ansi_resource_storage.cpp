#include "ansi_resource_storage.h"

#include "resource/shader/ansi_shader.h"
#include "resource/geometry/ansi_geometry.h"
#include "resource/vertex_array/ansi_vertex_array.h"
#include "resource/texture/ansi_texture.h"
#include "utility/shader_loader/ansi_shader_loader.h"
#include "utility/texture_loader/ansi_texture_loader.h"

namespace AN
{

	ResourceStorage::ResourceStorage()
	{

	}

	ResourceStorage::~ResourceStorage()
	{
		for (auto iter = m_shaders.begin(); iter != m_shaders.end(); ++iter) { AN_DELETE(*iter); }
		for (auto iter = m_geometries.begin(); iter != m_geometries.end(); ++iter) { AN_DELETE(*iter); }
		for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter) { AN_DELETE(*iter); }
	}

	Shader * ResourceStorage::CreateShader(const std::string & filePath, RenderType type)
	{
		unsigned shaderId{ 0 };
		if (!ShaderLoader::Load(filePath, shaderId)) { return nullptr; }
		m_shaders.push_back(new Shader(shaderId, type));
		return m_shaders.back();
	}

	Geometry * ResourceStorage::CreateGeometry()
	{
		m_geometries.push_back(new Geometry());
		return m_geometries.back();
	}

	Texture * ResourceStorage::CreateTexture(const std::string & filePath)
	{
		unsigned textureId{ 0 };
		int width{ 0 };
		int height{ 0 };
		if (!TextureLoader::Load(filePath, width, height, textureId)) { return nullptr; }
		m_textures.push_back(new Texture(textureId, static_cast<unsigned>(width), static_cast<unsigned>(height)));
		return m_textures.back();
	}

}
