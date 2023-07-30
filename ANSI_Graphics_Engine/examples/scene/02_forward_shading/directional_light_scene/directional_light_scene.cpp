#include "directional_light_scene.h"

#include "material/directional_light/directional_light_material.h"

namespace Example
{

	const std::string DirectionalLightScene::m_SceneName{ "04 - Directional Light" };

	DirectionalLightScene::DirectionalLightScene() :
		m_specularIntensity(2.0f),
		m_specularPower(32.0f),
		m_lightColor(0.75f, 0.75f, 0.75f),
		m_lightRotation(90.0f, 0.0f)
	{

	}

	bool DirectionalLightScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Directional Light === */
		m_directionalLight = AddObject(new AN::Object("Directional Light"));
		m_directionalLight->GetTransform()->SetRotationX(m_lightRotation.x);
		m_directionalLight->GetTransform()->SetRotationY(m_lightRotation.y);

		auto directionalLight = m_directionalLight->AddComponent<AN::DirectionalLight>();

		/* === RG Rat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto rgratMaterial = new DirectionalLightMaterial(m_directionalLightShader, directionalLight);
		rgratMaterial->SetSpecularIntensity(m_specularIntensity);
		rgratMaterial->SetSpecularPower(m_specularPower);
		auto rgratRenderer = m_rgrat->AddComponent<AN::Renderer>(rgratMaterial);
		rgratRenderer->GetInput()->SetGeometry(m_rgratVA);

		/* === Plane Object === */
		m_plane = AddObject(new AN::Object("Plane"));
		m_plane->GetTransform()->SetPositionY(-15.0f);
		m_plane->GetTransform()->SetRotationX(-90.0f);

		auto planeMaterial = new DirectionalLightMaterial(m_directionalLightShader, directionalLight);
		auto planeRenderer = m_plane->AddComponent<AN::Renderer>(planeMaterial);
		planeRenderer->GetInput()->SetGeometry(m_planeVA);

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool DirectionalLightScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		if (ImGui::DragFloat("Specular Intensity", &m_specularIntensity, 0.01f, 0.0f, 3.0f))
		{
			static_cast<DirectionalLightMaterial *>(m_rgrat->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularIntensity(m_specularIntensity);
		}

		if (ImGui::DragFloat("Specular Power", &m_specularPower, 0.25f, 1.0f, 50.0f))
		{
			static_cast<DirectionalLightMaterial *>(m_rgrat->FindComponent<AN::Renderer>()->GetMaterial())->SetSpecularPower(m_specularPower);
		}

		if (ImGui::ColorEdit3("Light Color", &m_lightColor.x))
		{
			m_directionalLight->FindComponent<AN::DirectionalLight>()->SetColor(m_lightColor);
		}

		if (ImGui::DragFloat2("Light Rotation", &m_lightRotation.x, 1.0f, -360.0f, 360.0f))
		{
			m_directionalLight->GetTransform()->SetRotationX(m_lightRotation.x);
			m_directionalLight->GetTransform()->SetRotationY(m_lightRotation.y);
		}

		return ExampleScene::OnRenderGui();
	}

	bool DirectionalLightScene::CreateResources()
	{
		/* === Shader === */
		/* Directional Light */
		AN_CHECK(m_directionalLightShader = GetResources()->CreateShader("assets/shader/directional_light.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* RG Rat */
		auto rgratGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* Plane */
		auto planeGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(planeGeometry->GeneratePlane(200.0f, 200.0f, 1, 1));

		/* RG Rat VA */
		AN_CHECK(m_rgratVA = rgratGeometry->GenerateVertexArray(AN::NORMAL));
		/* Plane VA */
		AN_CHECK(m_planeVA = planeGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

}
