#include "05_point_lights_scene.h"

#include "../examples/shader/point_light/point_lights_3_shader.h"

namespace Example
{

	const std::string PointLightsScene::m_SceneName{ "05 - Three Point Lights" };
	const float PointLightsScene::m_DefaultSpecularIntensity{ 1.0f };
	const float PointLightsScene::m_DefaultSpecularPower{ 32.0f };
	const float PointLightsScene::m_DefaultLightDistance{ 30.0f };
	const float PointLightsScene::m_DefaultLightRadius{ 100.0f };
	const glm::vec3 PointLightsScene::m_DefaultLightColors[m_PointLightCount]{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	PointLightsScene::PointLightsScene() :
		m_isWireframe(false),
		m_specularIntensity(m_DefaultSpecularIntensity),
		m_specularPower(m_DefaultSpecularPower),
		m_lightRadius(m_DefaultLightRadius),
		m_lightRotation(0.0f),
		m_lightDistance(m_DefaultLightDistance),
		m_lightHeights(0.0f, 0.0f, 0.0f)
	{

	}

	bool PointLightsScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Light Group === */
		m_lightGroup = AddObject(new AN::Object("Light Group"));

		/* === Point Lights === */
		AN::PointLight * pointLights[m_PointLightCount]{ nullptr, };
		for (unsigned i{ 0 }; i < m_PointLightCount; ++i)
		{
			m_lightGroup->AddChild(m_pointLights[i] = new AN::Object(std::string("Point Light ") + std::to_string(i)));

			pointLights[i] = m_pointLights[i]->AddComponent<AN::PointLight>(m_DefaultLightRadius, m_DefaultLightColors[i]);
			pointLights[i]->SetSpecularIntensity(m_DefaultSpecularIntensity);
			pointLights[i]->SetSpecularPower(m_DefaultSpecularPower);
		}
		UpdateLightDistance(m_DefaultLightDistance);

		/* === RG Rat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto rgratPointLights3Shader = new PointLights3Shader(m_pointLights3Shader, m_rgrat, pointLights);
		auto rgratRenderer = m_rgrat->AddComponent<AN::Renderer>(rgratPointLights3Shader);
		rgratRenderer->Input()->SetVertices(m_rgratVA->GetId(), m_rgratGeometry->GetVertexCount());
		rgratRenderer->Input()->SetIndices(m_rgratGeometry->GetIndexBufferId(), m_rgratGeometry->GetIndexCount());

		/* === Plane Object === */
		m_plane = AddObject(new AN::Object("Plane"));
		m_plane->GetTransform()->SetPositionY(-15.0f);
		m_plane->GetTransform()->SetRotationX(-90.0f);

		auto planePointLights3Shader = new PointLights3Shader(m_pointLights3Shader, m_plane, pointLights);
		auto planeRenderer = m_plane->AddComponent<AN::Renderer>(planePointLights3Shader);
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

	bool PointLightsScene::OnUpdate()
	{
		return true;
	}

	bool PointLightsScene::OnRenderGui()
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
			for (unsigned i{ 0 }; i < m_PointLightCount; ++i)
			{
				m_pointLights[i]->FindComponent<AN::PointLight>()->SetSpecularIntensity(m_specularIntensity);
			}
		}

		if (ImGui::DragFloat("Specular Power", &m_specularPower, 0.25f, 1.0f, 50.0f))
		{
			for (unsigned i{ 0 }; i < m_PointLightCount; ++i)
			{
				m_pointLights[i]->FindComponent<AN::PointLight>()->SetSpecularPower(m_specularPower);
			}
		}

		if (ImGui::DragFloat("Light Radius", &m_lightRadius, 1.0f, 0.0f, 200.0f))
		{
			for (unsigned i{ 0 }; i < m_PointLightCount; ++i)
			{
				m_pointLights[i]->FindComponent<AN::PointLight>()->SetRadius(m_lightRadius);
			}
		}

		if (ImGui::DragFloat("Light Rotation", &m_lightRotation, 1.0f, -360.0f, 360.0f))
		{
			m_lightGroup->GetTransform()->SetRotationY(m_lightRotation);
		}

		if (ImGui::DragFloat("Light Distance", &m_lightDistance, 0.1f, 0.0f, 50.0f))
		{
			UpdateLightDistance(m_lightDistance);
		}

		if (ImGui::DragFloat3("Light Heights", &m_lightHeights.x, 0.1f, -10.0f, 30.0f))
		{
			for (unsigned i{ 0 }; i < m_PointLightCount; ++i)
			{
				m_pointLights[i]->GetTransform()->SetPositionY(m_lightHeights[i]);
			}
		}

		return ExampleScene::OnRenderGui();
	}

	bool PointLightsScene::CreateResources()
	{
		/* === Shaders === */
		/* Point Lights 3 */
		AN_CHECK(m_pointLights3Shader = GetResources()->CreateShader("assets/shader/point_lights_3.shader", RenderType::Forward));

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

	void PointLightsScene::UpdateLightDistance(float distance)
	{
		float cos{ std::cos(glm::radians(30.0f)) * distance };
		float sin{ std::sin(glm::radians(30.0f)) * distance };
		m_pointLights[0]->GetTransform()->SetPosition(-cos, m_lightHeights[0], sin);
		m_pointLights[1]->GetTransform()->SetPosition(cos, m_lightHeights[1], sin);
		m_pointLights[2]->GetTransform()->SetPosition(0.0f, m_lightHeights[2], -std::sin(PI * 0.5f) * distance);
	}

}
