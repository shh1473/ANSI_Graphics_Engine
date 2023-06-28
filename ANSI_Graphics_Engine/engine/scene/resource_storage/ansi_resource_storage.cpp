#include "ansi_resource_storage.h"

#include "resource/shader/ansi_shader.h"
#include "resource/geometry/ansi_geometry.h"
#include "resource/vertex_array/ansi_vertex_array.h"
#include "utility/shader_loader/ansi_shader_loader.h"

namespace AN
{

	ResourceStorage::ResourceStorage()
	{

	}

	ResourceStorage::~ResourceStorage()
	{
		for (auto iter = m_shaders.begin(); iter != m_shaders.end(); ++iter) { AN_DELETE(*iter); }
		for (auto iter = m_geometries.begin(); iter != m_geometries.end(); ++iter) { AN_DELETE(*iter); }
	}

	Shader * ResourceStorage::CreateShader(const std::string & filePath, RenderType type)
	{
		unsigned shaderId{ 0 };
		if (!ShaderLoader::LoadShader(filePath, shaderId)) { return nullptr; }
		m_shaders.push_back(new Shader(shaderId, type));
		return m_shaders.back();
	}

	Geometry * ResourceStorage::CreateGeometry()
	{
		m_geometries.push_back(new Geometry());
		return m_geometries.back();
	}

}
