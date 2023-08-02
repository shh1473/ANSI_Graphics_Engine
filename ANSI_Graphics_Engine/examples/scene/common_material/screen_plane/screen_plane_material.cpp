#include "screen_plane_material.h"

namespace Example
{

	ScreenPlaneMaterial::ScreenPlaneMaterial(AN::Shader * shader, unsigned textureId, const glm::vec4 & viewport) :
		Material(shader),
		m_viewport(viewport)
	{
		m_isEnableDepthTest = false;
		m_isEnableDepthWrite = false;

		m_textureIds[0] = textureId;
	}

	bool ScreenPlaneMaterial::OnUpdateUniforms()
	{
		m_cameraSize.Set(AN::Core::GetRender()->GetCurrentCamera()->GetSize());

		if (m_cameraSize.Check())
		{
			glm::vec2 halfCameraSize{ AN::Core::GetRender()->GetCurrentCamera()->GetSize() * 0.5f };

			m_transform->SetScaleX(m_viewport[2] / halfCameraSize.x);
			m_transform->SetScaleY(m_viewport[3] / halfCameraSize.y);
			m_transform->SetPositionX((m_viewport[0] / halfCameraSize.x) + (m_transform->GetScale().x * 0.5f) - 1.0f);
			m_transform->SetPositionY((m_viewport[1] / halfCameraSize.y) + (m_transform->GetScale().y * 0.5f) - 1.0f);
		}

		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_transform->GetWorldMatrix()));

		/* === Fragment === */
		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		AN_CHECK(SetUniform1i("u_diffuseMap", 0));

		return true;
	}

}
