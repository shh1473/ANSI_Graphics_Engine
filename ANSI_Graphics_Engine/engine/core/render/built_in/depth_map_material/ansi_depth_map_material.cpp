#include "ansi_depth_map_material.h"

#include "core/render/ansi_render.h"
#include "object/component/camera/ansi_camera.h"
#include "object/component/transform/ansi_transform.h"

namespace AN
{

	DepthMapMaterial::DepthMapMaterial(Shader * shader) :
		Material(shader)
	{

	}

	bool DepthMapMaterial::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));

		return true;
	}

}
