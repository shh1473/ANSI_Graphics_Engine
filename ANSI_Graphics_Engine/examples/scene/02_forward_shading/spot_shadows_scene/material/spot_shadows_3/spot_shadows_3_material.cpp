#include "spot_shadows_3_material.h"

namespace Example
{

	SpotShadows3Material::SpotShadows3Material(AN::Shader * shader, AN::SpotLight ** lights) :
		Material(shader),
		m_lights{ nullptr, }
	{
		for (unsigned i{ 0 }; i < 3; ++i) {
			m_lights[i] = lights[i];
			m_textureIds[i] = lights[i]->GetShadowMapCamera()->GetDepthTexture()->GetId();
		}
	}

	bool SpotShadows3Material::OnUpdateUniforms()
	{
		/* === Vertex === */
		static glm::mat4 lightMVPs[3];

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			lightMVPs[i] = m_lights[i]->GetShadowMapCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix();
		}

		AN_CHECK(SetUniform4x4fv("u_lightMVPs", 3, &lightMVPs[0][0][0]));

		AN_CHECK(SetUniform4x4f("u_MVP", AN::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * m_transform->GetWorldMatrix()));
		AN_CHECK(SetUniform4x4f("u_worldMatrix", m_transform->GetWorldMatrix()));

		/* === Fragment === */
		static float lightRadiusRcps[3];
		static float lightSmoothRangeRcps[3];
		static float lightCosAngles[3];
		static glm::vec3 lightColors[3];
		static glm::vec3 lightPositions[3];
		static glm::vec3 lightDirections[3];
		static int shadowMaps[3] = { 0, 1, 2 };

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			lightRadiusRcps[i] = m_lights[i]->GetRadiusRcp();
			lightSmoothRangeRcps[i] = m_lights[i]->GetSmoothRangeRcp();
			lightCosAngles[i] = m_lights[i]->GetCosAngle();
			lightColors[i] = m_lights[i]->GetColor();
			lightPositions[i] = m_lights[i]->GetObject()->GetTransform()->GetWorldPosition();
			lightDirections[i] = m_lights[i]->GetObject()->GetTransform()->GetLookAt();
		}

		AN_CHECK(SetUniform3f("u_cameraPosition", AN::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		AN_CHECK(SetUniform1fv("u_lightRadiusRcps", 3, &lightRadiusRcps[0]));
		AN_CHECK(SetUniform1fv("u_lightSmoothRangeRcps", 3, &lightSmoothRangeRcps[0]));
		AN_CHECK(SetUniform1fv("u_lightCosAngles", 3, &lightCosAngles[0]));
		AN_CHECK(SetUniform3fv("u_lightColors", 3, &lightColors[0].x));
		AN_CHECK(SetUniform3fv("u_lightPositions", 3, &lightPositions[0].x));
		AN_CHECK(SetUniform3fv("u_lightDirections", 3, &lightDirections[0].x));
		AN_CHECK(SetUniform1iv("u_shadowMaps", 3, &shadowMaps[0]));

		AN_CHECK(SetUniform1f("u_specularIntensity", m_specularIntensity));
		AN_CHECK(SetUniform1f("u_specularPower", m_specularPower));
		AN_CHECK(SetUniform4f("u_diffuseColor", m_diffuseColor));

		return true;
	}

}
