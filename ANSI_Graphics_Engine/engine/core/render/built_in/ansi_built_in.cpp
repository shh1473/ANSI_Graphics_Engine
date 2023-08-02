#include "ansi_built_in.h"

#include "common/ansi_common_render.h"
#include "resource/shader/ansi_shader.h"
#include "utility/shader_loader/ansi_shader_loader.h"

#include "depth_map_material/ansi_depth_map_material.h"

namespace AN
{

	BuiltIn::BuiltIn() :
		m_depthMapShader(nullptr),
		m_depthMapMaterial(nullptr)
	{

	}

	BuiltIn::~BuiltIn()
	{
		AN_DELETE(m_depthMapShader);
		AN_DELETE(m_depthMapMaterial);
	}

	bool BuiltIn::Initialize()
	{
		unsigned depthMapShaderId{ 0 };
		AN_CHECK(ShaderLoader::Load("assets/shader/depth_map.shader", depthMapShaderId));
		m_depthMapShader = new Shader(depthMapShaderId, RenderType::Forward);
		m_depthMapMaterial = new DepthMapMaterial(m_depthMapShader);

		return true;
	}

}
