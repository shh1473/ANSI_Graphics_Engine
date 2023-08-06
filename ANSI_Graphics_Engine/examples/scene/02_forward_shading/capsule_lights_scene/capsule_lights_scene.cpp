#include "capsule_lights_scene.h"

#include "material/capsule_lights_3/capsule_lights_3_material.h"

namespace Example
{

	const std::string CapsuleLightsScene::m_SceneName{ "Three Capsule Lights" };

	CapsuleLightsScene::CapsuleLightsScene() :
		m_specularIntensity(1.0f),
		m_specularPower(32.0f),
		m_lightRadius(100.0f),
		m_lightLength(100.0f),
		m_lightRotation(0.0f),
		m_lightDistance(30.0f),
		m_lightHeights(0.0f, 0.0f, 0.0f)
	{

	}

	bool CapsuleLightsScene::Initialize()
	{
		/* === Light Group === */
		m_lightGroup = AddObject(new AN::Object("Light Group"));

		/* === Capsule Light Objects === */
		AN::CapsuleLight * capsuleLights[3]{ nullptr, };

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			m_lightGroup->AddChild(m_capsuleLights[i] = new AN::Object(std::string("Capsule Light ") + std::to_string(i + 1)));

			capsuleLights[i] = m_capsuleLights[i]->AddComponent<AN::CapsuleLight>(m_lightRadius, m_lightLength, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		capsuleLights[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		capsuleLights[1]->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
		capsuleLights[2]->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		m_capsuleLights[0]->GetTransform()->SetRotationY(30.0f);
		m_capsuleLights[1]->GetTransform()->SetRotationY(-30.0f);
		m_capsuleLights[2]->GetTransform()->SetRotationY(90.0f);
		UpdateLightDistance(m_lightDistance);

		/* === RG Rat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto rgratMaterial = new CapsuleLights3Material(m_capsuleLights3Shader, capsuleLights);
		rgratMaterial->SetSpecularIntensity(m_specularIntensity);
		rgratMaterial->SetSpecularPower(m_specularPower);
		m_rgrat->AddComponent<AN::Renderer>(m_rgratVA, rgratMaterial);

		/* === Plane Object === */
		m_plane = AddObject(new AN::Object("Plane"));
		m_plane->GetTransform()->SetPositionY(-15.0f);
		m_plane->GetTransform()->SetRotationX(-90.0f);

		auto planeMaterial = new CapsuleLights3Material(m_capsuleLights3Shader, capsuleLights);
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

	bool CapsuleLightsScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::DragFloat("Specular Intensity", &m_specularIntensity, 0.01f, 0.0f, 3.0f))
		{
			static_cast<CapsuleLights3Material *>(m_rgrat->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularIntensity(m_specularIntensity);
			static_cast<CapsuleLights3Material *>(m_plane->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularIntensity(m_specularIntensity);
		}

		if (ImGui::DragFloat("Specular Power", &m_specularPower, 0.25f, 1.0f, 50.0f))
		{
			static_cast<CapsuleLights3Material *>(m_rgrat->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularPower(m_specularPower);
			static_cast<CapsuleLights3Material *>(m_plane->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularPower(m_specularPower);
		}

		if (ImGui::DragFloat("Light Radius", &m_lightRadius, 0.25f, 0.0f, 200.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_capsuleLights[i]->FindComponent<AN::CapsuleLight>()->SetRadius(m_lightRadius); }
		}

		if (ImGui::DragFloat("Light Length", &m_lightLength, 0.25f, 0.0f, 200.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_capsuleLights[i]->FindComponent<AN::CapsuleLight>()->SetLength(m_lightLength); }
		}

		if (ImGui::DragFloat3("Light Heights", &m_lightHeights.x, 0.1f, -10.0f, 30.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_capsuleLights[i]->GetTransform()->SetPositionY(m_lightHeights[i]); }
		}

		if (ImGui::DragFloat("Light Rotation", &m_lightRotation, 1.0f, -360.0f, 360.0f))
		{
			m_lightGroup->GetTransform()->SetRotationY(m_lightRotation);
		}

		if (ImGui::DragFloat("Light Distance", &m_lightDistance, 0.1f, 0.0f, 50.0f))
		{
			UpdateLightDistance(m_lightDistance);
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return ExampleScene::OnRenderGui();
	}

	bool CapsuleLightsScene::CreateResources()
	{
		/* === Shader === */
		/* Capsule Lights 3 */
		AN_CHECK(m_capsuleLights3Shader = GetResources()->CreateShader("assets/shader/capsule_lights_3.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* RG Rat */
		auto rgratGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(rgratGeometry->GenerateFromObj("assets/model/pn_rgrat.obj"));
		/* Plane */
		auto planeGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(planeGeometry->GeneratePlane(200.0f, 200.0f));

		/* RG Rat VA */
		AN_CHECK(m_rgratVA = rgratGeometry->GenerateVertexArray(AN::NORMAL));
		/* Plane VA */
		AN_CHECK(m_planeVA = planeGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

	void CapsuleLightsScene::UpdateLightDistance(float distance)
	{
		float cos{ std::cos(glm::radians(30.0f)) * distance };
		float sin{ std::sin(glm::radians(30.0f)) * distance };

		m_capsuleLights[0]->GetTransform()->SetPosition(-cos, m_lightHeights[0], sin);
		m_capsuleLights[1]->GetTransform()->SetPosition(cos, m_lightHeights[1], sin);
		m_capsuleLights[2]->GetTransform()->SetPosition(0.0f, m_lightHeights[2], -std::sin(PI * 0.5f) * distance);
	}

}
