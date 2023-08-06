#include "ansi_depth_spot_material.h"

#include "core/render/ansi_render.h"
#include "object/component/camera/ansi_camera.h"
#include "object/component/transform/ansi_transform.h"

namespace AN
{

	DepthSpotMaterial::DepthSpotMaterial(Shader * shader) :
		Material(shader)
	{

	}

	bool DepthSpotMaterial::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));

		return true;
	}

}
