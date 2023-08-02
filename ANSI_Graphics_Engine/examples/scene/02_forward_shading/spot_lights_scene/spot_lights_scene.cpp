#include "spot_lights_scene.h"

#include "material/spot_lights_3/spot_lights_3_material.h"

namespace Example
{

	const std::string SpotLightsScene::m_SceneName{ "Three Spot Lights" };

	SpotLightsScene::SpotLightsScene() :
		m_specularIntensity(1.0f),
		m_specularPower(32.0f),
		m_lightRadius(200.0f),
		m_lightAngle(90.0f),
		m_lightSmoothRange(0.2f),
		m_lightRotation(0.0f),
		m_lightDistance(60.0f),
		m_lightRotationXs(20.0f)
	{

	}

	bool SpotLightsScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Light Group === */
		m_lightGroup = AddObject(new AN::Object("Light Group"));

		/* === Spot Light Objects === */
		AN::SpotLight * spotLights[3]{ nullptr, };

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			m_lightGroup->AddChild(m_spotLights[i] = new AN::Object(std::string("Spot Light ") + std::to_string(i + 1)));
			m_spotLights[i]->GetTransform()->SetPositionY(50.0f);

			spotLights[i] = m_spotLights[i]->AddComponent<AN::SpotLight>(m_lightRadius, m_lightAngle, m_lightSmoothRange);
		}

		spotLights[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		spotLights[1]->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
		spotLights[2]->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		m_spotLights[0]->GetTransform()->SetRotation(m_lightRotationXs.x, 120.0f, 0.0f, EulerOrder::YXZ);
		m_spotLights[1]->GetTransform()->SetRotation(m_lightRotationXs.y, -120.0f, 0.0f, EulerOrder::YXZ);
		m_spotLights[2]->GetTransform()->SetRotation(m_lightRotationXs.z, 0.0f, 0.0f, EulerOrder::YXZ);
		UpdateLightDistance(m_lightDistance);

		/* === RG Rat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto rgratMaterial = new SpotLights3Material(m_spotLights3Shader, spotLights);
		rgratMaterial->SetSpecularIntensity(m_specularIntensity);
		rgratMaterial->SetSpecularPower(m_specularPower);
		m_rgrat->AddComponent<AN::Renderer>(m_rgratVA, rgratMaterial);

		/* === Plane Object === */
		m_plane = AddObject(new AN::Object("Plane"));
		m_plane->GetTransform()->SetPositionY(-15.0f);
		m_plane->GetTransform()->SetRotationX(-90.0f);

		auto planeMaterial = new SpotLights3Material(m_spotLights3Shader, spotLights);
		planeMaterial->SetSpecularIntensity(m_specularIntensity);
		planeMaterial->SetSpecularPower(m_specularPower);
		m_plane->AddComponent<AN::Renderer>(m_planeVA, planeMaterial);

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool SpotLightsScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::DragFloat("Specular Intensity", &m_specularIntensity, 0.01f, 0.0f, 3.0f))
		{
			static_cast<SpotLights3Material *>(m_rgrat->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularIntensity(m_specularIntensity);
			static_cast<SpotLights3Material *>(m_plane->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularIntensity(m_specularIntensity);
		}

		if (ImGui::DragFloat("Specular Power", &m_specularPower, 0.25f, 1.0f, 50.0f))
		{
			static_cast<SpotLights3Material *>(m_rgrat->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularPower(m_specularPower);
			static_cast<SpotLights3Material *>(m_plane->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularPower(m_specularPower);
		}

		if (ImGui::DragFloat("Light Radius", &m_lightRadius, 1.0f, 0.0f, 300.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_spotLights[i]->FindComponent<AN::SpotLight>()->SetRadius(m_lightRadius); }
		}

		if (ImGui::DragFloat("Light Angle", &m_lightAngle, 1.0f, 0.0f, 180.0f))
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
			UpdateLightDistance(m_lightDistance);
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return ExampleScene::OnRenderGui();
	}

	bool SpotLightsScene::CreateResources()
	{
		/* === Shader === */
		/* Spot Lights 3 */
		AN_CHECK(m_spotLights3Shader = GetResources()->CreateShader("assets/shader/spot_lights_3.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* RG Rat */
		auto rgratGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* Plane */
		auto planeGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(planeGeometry->GeneratePlane(200.0f, 200.0f));

		/* RG Rat VA */
		AN_CHECK(m_rgratVA = rgratGeometry->GenerateVertexArray(AN::NORMAL));
		/* Plane VA */
		AN_CHECK(m_planeVA = planeGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

	void SpotLightsScene::UpdateLightDistance(float distance)
	{
		float cos{ std::cos(glm::radians(30.0f)) * distance };
		float sin{ std::sin(glm::radians(30.0f)) * distance };

		m_spotLights[0]->GetTransform()->SetPosition(-cos, 0.0f, sin);
		m_spotLights[1]->GetTransform()->SetPosition(cos, 0.0f, sin);
		m_spotLights[2]->GetTransform()->SetPosition(0.0f, 0.0f, -std::sin(PI * 0.5f) * distance);
	}

}
