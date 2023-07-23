#include "04_directional_light_scene.h"

#include "../examples/shader/directional_light/directional_light_shader.h"

namespace Example
{

	const std::string DirectionalLightScene::m_SceneName{ "04 - Directional Light" };
	const float DirectionalLightScene::m_DefaultSpecularIntensity{ 2.0f };
	const float DirectionalLightScene::m_DefaultSpecularPower{ 32.0f };
	const glm::vec3 DirectionalLightScene::m_DefaultLightColor{ 0.75f, 0.75f, 0.75f };
	const glm::vec2 DirectionalLightScene::m_DefaultLightRotation{ 90.0f, 0.0f };

	DirectionalLightScene::DirectionalLightScene() :
		m_isWireframe(false),
		m_specularIntensity(m_DefaultSpecularIntensity),
		m_specularPower(m_DefaultSpecularPower),
		m_lightColor(m_DefaultLightColor),
		m_lightRotation(m_DefaultLightRotation)
	{

	}

	bool DirectionalLightScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Directional Light === */
		m_directionalLight = AddObject(new AN::Object("Directional Light"));
		m_directionalLight->GetTransform()->SetRotationX(m_DefaultLightRotation.x);
		m_directionalLight->GetTransform()->SetRotationY(m_DefaultLightRotation.y);

		auto directionalLight = m_directionalLight->AddComponent<AN::DirectionalLight>(m_DefaultLightColor);
		directionalLight->SetSpecularIntensity(m_DefaultSpecularIntensity);

		/* === RG Rat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto rgratDirectionalLightShader = new DirectionalLightShader(m_directionalLightShader, m_rgrat, directionalLight);
		auto rgratRenderer = m_rgrat->AddComponent<AN::Renderer>(rgratDirectionalLightShader);
		rgratRenderer->Input()->SetVertices(m_rgratVA->GetId(), m_rgratGeometry->GetVertexCount());
		rgratRenderer->Input()->SetIndices(m_rgratGeometry->GetIndexBufferId(), m_rgratGeometry->GetIndexCount());

		/* === Plane Object === */
		m_plane = AddObject(new AN::Object("Plane"));
		m_plane->GetTransform()->SetPositionY(-15.0f);
		m_plane->GetTransform()->SetRotationX(-90.0f);

		auto planeDirectionalLightShader = new DirectionalLightShader(m_directionalLightShader, m_plane, directionalLight);
		auto planeRenderer = m_plane->AddComponent<AN::Renderer>(planeDirectionalLightShader);
		planeRenderer->Input()->SetVertices(m_planeVA->GetId(), m_planeGeometry->GetVertexCount());
		planeRenderer->Input()->SetIndices(m_planeGeometry->GetIndexBufferId(), m_planeGeometry->GetIndexCount());

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool DirectionalLightScene::OnUpdate()
	{
		return true;
	}

	bool DirectionalLightScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::Checkbox("Wireframe", &m_isWireframe))
		{
			m_camera->FindComponent<AN::Camera>()->Raster()->SetFillMode((m_isWireframe) ? AN::FillMode::Line : AN::FillMode::Fill);
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		if (ImGui::DragFloat("Specular Intensity", &m_specularIntensity, 0.01f, 0.0f, 3.0f))
		{
			m_directionalLight->FindComponent<AN::DirectionalLight>()->SetSpecularIntensity(m_specularIntensity);
		}

		if (ImGui::DragFloat("Specular Power", &m_specularPower, 0.25f, 1.0f, 50.0f))
		{
			m_directionalLight->FindComponent<AN::DirectionalLight>()->SetSpecularPower(m_specularPower);
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
		/* === Shaders === */
		/* Directional Light */
		AN_CHECK(m_directionalLightShader = GetResources()->CreateShader("assets/shader/directional_light.shader", RenderType::Forward));

		/* === Geometries === */
		/* RG Rat */
		AN_CHECK(m_rgratGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* RG Rat VA */
		AN_CHECK(m_rgratVA = m_rgratGeometry->GenerateVertexArray(AN::NORMAL));

		/* Plane */
		AN_CHECK(m_planeGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_planeGeometry->GeneratePlane(200.0f, 200.0f, 1, 1));
		/* Plane VA */
		AN_CHECK(m_planeVA = m_planeGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

}
