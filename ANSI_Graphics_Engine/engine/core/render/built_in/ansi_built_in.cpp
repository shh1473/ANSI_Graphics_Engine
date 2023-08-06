#include "ansi_built_in.h"

#include "common/ansi_common_render.h"
#include "resource/shader/ansi_shader.h"
#include "utility/shader_loader/ansi_shader_loader.h"

#include "depth_spot_material/ansi_depth_spot_material.h"
#include "depth_point_material/ansi_depth_point_material.h"

namespace AN
{

	BuiltIn::BuiltIn() :
		m_depthSpotShader(nullptr),
		m_depthPointShader(nullptr),
		m_depthSpotMaterial(nullptr),
		m_depthPointMaterial(nullptr)
	{

	}

	BuiltIn::~BuiltIn()
	{
		AN_DELETE(m_depthSpotShader);
		AN_DELETE(m_depthPointShader);

		AN_DELETE(m_depthSpotMaterial);
		AN_DELETE(m_depthPointMaterial);
	}

	bool BuiltIn::Initialize()
	{
		unsigned depthSpotShaderId{ 0 };
		AN_CHECK(ShaderLoader::Load("assets/shader/depth_spot.shader", depthSpotShaderId));
		m_depthSpotShader = new Shader(depthSpotShaderId, RenderType::Forward);
		m_depthSpotMaterial = new DepthSpotMaterial(m_depthSpotShader);

		unsigned depthPointShaderId{ 0 };
		AN_CHECK(ShaderLoader::Load("assets/shader/depth_point.shader", depthPointShaderId));
		m_depthPointShader = new Shader(depthPointShaderId, RenderType::Forward);
		m_depthPointMaterial = new DepthPointMaterial(m_depthPointShader);

		return true;
	}

}
