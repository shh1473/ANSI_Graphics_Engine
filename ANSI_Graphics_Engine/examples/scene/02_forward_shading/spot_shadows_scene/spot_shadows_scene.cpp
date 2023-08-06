#include "spot_shadows_scene.h"

#include "object/component/camera/depth_spot_camera/ansi_depth_spot_camera.h"

#include "../../common_material/screen_plane/screen_plane_material.h"
#include "material/spot_shadows_3/spot_shadows_3_material.h"

namespace Example
{

	const std::string SpotShadowsScene::m_SceneName{ "Three Spot Shadows" };

	SpotShadowsScene::SpotShadowsScene() :
		m_isVisibleShadowMaps(false),
		m_lightRadius(300.0f),
		m_lightAngle(70.0f),
		m_lightSmoothRange(0.5f),
		m_lightRotation(0.0f),
		m_lightDistance(30.0f),
		m_lightRotationXs(60.0f)
	{

	}

	bool SpotShadowsScene::Initialize()
	{
		/* === Light Group === */
		m_lightGroup = AddObject(new AN::Object("Light Group"));

		/* === Spot Light Object === */
		AN::SpotLight * spotLights[3]{ nullptr, };

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			m_lightGroup->AddChild(m_spotLights[i] = new AN::Object(std::string("Spot Light ") + std::to_string(i + 1)));

			spotLights[i] = m_spotLights[i]->AddComponent<AN::SpotLight>(m_lightRadius, m_lightAngle, m_lightSmoothRange);
			AN_CHECK(spotLights[i]->CastShadow());
		}

		m_lightGroup->GetTransform()->SetPositionY(50.0f);
		spotLights[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		spotLights[1]->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
		spotLights[2]->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		m_spotLights[0]->GetTransform()->SetRotation(m_lightRotationXs.x, 120.0f, 0.0f, EulerOrder::YXZ);
		m_spotLights[1]->GetTransform()->SetRotation(m_lightRotationXs.y, -120.0f, 0.0f, EulerOrder::YXZ);
		m_spotLights[2]->GetTransform()->SetRotation(m_lightRotationXs.z, 0.0f, 0.0f, EulerOrder::YXZ);
		UpdateLightDistance();

		/* === RG Rat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto rgratRenderer = m_rgrat->AddComponent<AN::Renderer>(m_rgratVA, new SpotShadows3Material(m_spotShadows3Shader, spotLights));

		/* === Plane Object === */
		m_plane = AddObject(new AN::Object("Plane"));
		m_plane->SetIsCastShadow(false);
		m_plane->GetTransform()->SetPositionY(-15.0f);
		m_plane->GetTransform()->SetRotationX(-90.0f);

		m_plane->AddComponent<AN::Renderer>(m_floorPlaneVA, new SpotShadows3Material(m_spotShadows3Shader, spotLights));

		/* === Shadow Plane Objects === */
		for (unsigned i{ 0 }; i < 3; ++i)
		{
			m_shadowPlanes[i] = AddObject(new AN::Object(std::string("Shadow Plane ") + std::to_string(i)));
			m_shadowPlanes[i]->SetIsEnabled(m_isVisibleShadowMaps);
			m_shadowPlanes[i]->SetIsCastShadow(false);

			auto shadowPlaneMaterial = new ScreenPlaneMaterial(m_screenPlaneShader,
				m_spotLights[i]->FindComponent<AN::SpotLight>()->GetShadowMapCamera()->GetDepthMap()->GetId(),
				glm::vec4(i * 200.0f + (i + 1) * 10.0f, 10.0f, 200.0f, 200.0f));
			m_shadowPlanes[i]->AddComponent<AN::Renderer>(m_shadowMapPlaneVA, shadowPlaneMaterial);
		}
		static_cast<ScreenPlaneMaterial *>(m_shadowPlanes[0]->FindComponent<AN::Renderer>()->GetMaterial())->SetDiffuseColor(glm::vec3(1.0f, 0.85f, 0.85f));
		static_cast<ScreenPlaneMaterial *>(m_shadowPlanes[1]->FindComponent<AN::Renderer>()->GetMaterial())->SetDiffuseColor(glm::vec3(0.85f, 1.0f, 0.85f));
		static_cast<ScreenPlaneMaterial *>(m_shadowPlanes[2]->FindComponent<AN::Renderer>()->GetMaterial())->SetDiffuseColor(glm::vec3(0.85f, 0.85f, 1.0f));

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool SpotShadowsScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::DragFloat("Light Radius", &m_lightRadius, 1.0f, 0.0f, 300.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_spotLights[i]->FindComponent<AN::SpotLight>()->SetRadius(m_lightRadius); }
		}

		if (ImGui::DragFloat("Light Angle", &m_lightAngle, 1.0f, 0.0f, 135.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_spotLights[i]->FindComponent<AN::SpotLight>()->SetAngle(m_lightAngle); }
		}

		if (ImGui::DragFloat("Light Smooth Range", &m_lightSmoothRange, 0.01f, 0.0f, 1.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_spotLights[i]->FindComponent<AN::SpotLight>()->SetSmoothRange(m_lightSmoothRange); }
		}

		if (ImGui::DragFloat3("Light Look At", &m_lightRotationXs.x, 0.5f, 0.0f, 180.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_spotLights[i]->GetTransform()->SetRotationX(m_lightRotationXs[i]); }
		}

		if (ImGui::DragFloat("Light Rotation", &m_lightRotation, 1.0f, -360.0f, 360.0f))
		{
			m_lightGroup->GetTransform()->SetRotationY(m_lightRotation);
		}

		if (ImGui::DragFloat("Light Distance", &m_lightDistance, 0.1f, 0.0f, 100.0f))
		{
			UpdateLightDistance();
		}

		if (ImGui::Checkbox("Show Shadow Maps", &m_isVisibleShadowMaps))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_shadowPlanes[i]->SetIsEnabled(m_isVisibleShadowMaps); }
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return ExampleScene::OnRenderGui();
	}

	bool SpotShadowsScene::CreateResources()
	{
		/* === Shader === */
		/* Spot Shadows 3 */
		AN_CHECK(m_spotShadows3Shader = GetResources()->CreateShader("assets/shader/spot_shadows_3.shader", AN::RenderType::Forward));
		/* Screen Plane */
		AN_CHECK(m_screenPlaneShader = GetResources()->CreateShader("assets/shader/screen_plane.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* RG Rat */
		auto rgratGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* Floor Plane */
		auto floorPlaneGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(floorPlaneGeometry->GeneratePlane(200.0f, 200.0f));
		/* Shadow Map Plane */
		auto shadowMapPlaneGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(shadowMapPlaneGeometry->GeneratePlane(1.0f, 1.0f));

		/* RG Rat VA */
		AN_CHECK(m_rgratVA = rgratGeometry->GenerateVertexArray(AN::NORMAL));
		/* Floor Plane VA */
		AN_CHECK(m_floorPlaneVA = floorPlaneGeometry->GenerateVertexArray(AN::NORMAL));
		/* Shadow Map Plane VA */
		AN_CHECK(m_shadowMapPlaneVA = shadowMapPlaneGeometry->GenerateVertexArray(AN::TEXCOORD));

		return true;
	}

	void SpotShadowsScene::UpdateLightDistance()
	{
		float cos{ std::cos(glm::radians(30.0f)) * m_lightDistance };
		float sin{ std::sin(glm::radians(30.0f)) * m_lightDistance };

		m_spotLights[0]->GetTransform()->SetPosition(-cos, 0.0f, sin);
		m_spotLights[1]->GetTransform()->SetPosition(cos, 0.0f, sin);
		m_spotLights[2]->GetTransform()->SetPosition(0.0f, 0.0f, -std::sin(PI * 0.5f) * m_lightDistance);
	}

}
