#include "ansi_built_in_resources.h"

#include "common/ansi_common_render.h"
#include "resource/shader/ansi_shader.h"
#include "utility/shader_loader/ansi_shader_loader.h"

namespace AN
{

	BuiltInResources::BuiltInResources() :
		m_depthMapShader(nullptr)
	{

	}

	BuiltInResources::~BuiltInResources()
	{
		AN_DELETE(m_depthMapShader);
	}

	bool BuiltInResources::Initialize()
	{
		unsigned depthMapShaderId{ 0 };
		//AN_CHECK(ShaderLoader::LoadShader("<TODO>", depthMapShaderId));
		m_depthMapShader = new Shader(depthMapShaderId, RenderType::Packing);
		return true;
	}

}
