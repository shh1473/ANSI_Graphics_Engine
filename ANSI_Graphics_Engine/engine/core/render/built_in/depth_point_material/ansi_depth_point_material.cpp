#include "ansi_depth_point_material.h"

#include "core/render/ansi_render.h"
#include "object/component/camera/ansi_camera.h"
#include "object/component/transform/ansi_transform.h"
#include "object/component/camera/depth_point_camera/ansi_depth_point_camera.h"

namespace AN
{

	DepthPointMaterial::DepthPointMaterial(Shader * shader) :
		Material(shader)
	{
		
	}

	bool DepthPointMaterial::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_transform->GetWorldMatrix()));

		/* === Geometry === */
		AN_CHECK(SetUniform4x4fv("u_lightVPs", 6, static_cast<DepthPointCamera *>(Core::GetRender()->GetCurrentCamera())->GetViewProjMatricesAddress()));

		/* === Fragment === */
		AN_CHECK(SetUniform1f("u_radius", Core::GetRender()->GetCurrentCamera()->GetFar()));
		AN_CHECK(SetUniform3f("u_lightPosition", m_transform->GetPosition()));

		return true;
	}

}
