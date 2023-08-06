#include "point_shadows_3_material.h"

#include "object/component/camera/depth_point_camera/ansi_depth_point_camera.h"

namespace Example
{

	PointShadows3Material::PointShadows3Material(AN::Shader * shader, AN::PointLight ** lights) :
		Material(shader),
		m_lights{ nullptr, }
	{
		for (unsigned i{ 0 }; i < 3; ++i)
		{
			m_lights[i] = lights[i];

			m_textureIds[i] = lights[i]->GetShadowMapCamera()->GetDepthMap()->GetId();
			m_textureTypes[i] = AN::TextureType::Cube;
		}
	}

	bool PointShadows3Material::OnUpdateUniforms()
	{
		/* === Vertex === */
		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_transform->GetWorldMatrix()));

		/* === Fragment === */
		static int shadowMaps[3] = { 0, 1, 2 };
		static float lightCameraFars[3];
		static float lightRadiusRcps[3];
		static glm::vec3 lightColors[3];
		static glm::vec3 lightPositions[3];

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			lightCameraFars[i] = m_lights[i]->GetShadowMapCamera()->GetFar();
			lightRadiusRcps[i] = m_lights[i]->GetRadiusRcp();
			lightColors[i] = m_lights[i]->GetColor();
			lightPositions[i] = m_lights[i]->GetObject()->GetTransform()->GetWorldPosition();
		}

		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		AN_CHECK(SetUniform1fv("u_lightCameraFars", 3, &lightCameraFars[0]));
		AN_CHECK(SetUniform1fv("u_lightRadiusRcps", 3, &lightRadiusRcps[0]));
		AN_CHECK(SetUniform3fv("u_lightColors", 3, &lightColors[0].x));
		AN_CHECK(SetUniform3fv("u_lightPositions", 3, &lightPositions[0].x));

		AN_CHECK(SetUniform1f("u_specularIntensity", m_specularIntensity));
		AN_CHECK(SetUniform1f("u_specularPower", m_specularPower));
		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		AN_CHECK(SetUniform1iv("u_shadowMaps", 3, &shadowMaps[0]));

		return true;
	}

}
