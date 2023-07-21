#include "04_directional_light_scene.h"

#include "../examples/shader/directional_light/directional_light_shader.h"

namespace Example
{

	const float DirectionalLightScene::m_DefaultSpecularIntensity{ 3.0f };
	const float DirectionalLightScene::m_DefaultSpecularPower{ 32.0f };
	const glm::vec3 DirectionalLightScene::m_DefaultDirectionalLightColor{ 0.75f, 0.75f, 0.75f };
	const glm::vec3 DirectionalLightScene::m_DefaultDirectionalLightDirection{ 0.0f, -1.0f, -1.0f };

	DirectionalLightScene::DirectionalLightScene() :
		m_isWireframe(false),
		m_specularIntensity(m_DefaultSpecularIntensity),
		m_specularPower(m_DefaultSpecularPower),
		m_directionalLightColor(m_DefaultDirectionalLightColor),
		m_directionalLightDirection(m_DefaultDirectionalLightDirection)
	{

	}

	bool DirectionalLightScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle("04 - Directional Light");

		/* === Directional Light === */
		m_directionalLight = AddObject(new AN::Object("Directional Light"));

		auto directionalLight = m_directionalLight->AddComponent<AN::DirectionalLight>(m_DefaultDirectionalLightColor, m_DefaultDirectionalLightDirection);
		directionalLight->SetSpecularIntensity(m_DefaultSpecularIntensity);

		/* === RGRat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));
		m_rgrat->GetTransform()->SetScale(1.0f, 1.0f, 1.0f);

		auto directionalLightShader = new DirectionalLightShader(m_directionalLightShader, m_rgrat, directionalLight);
		auto rgratRenderer = m_rgrat->AddComponent<AN::Renderer>(directionalLightShader);
		rgratRenderer->Input()->SetVertices(m_rgratVA->GetId(), m_rgratGeometry->GetVertexCount());
		rgratRenderer->Input()->SetIndices(m_rgratGeometry->GetIndexBufferId(), m_rgratGeometry->GetIndexCount());

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

		if (ImGui::ColorEdit3("Color", &m_directionalLightColor.x))
		{
			m_directionalLight->FindComponent<AN::DirectionalLight>()->SetColor(m_directionalLightColor);
		}

		if (ImGui::DragFloat3("Direction", &m_directionalLightDirection.x, 0.01f, -1.0f, 1.0f))
		{
			m_directionalLight->FindComponent<AN::DirectionalLight>()->SetDirection(m_directionalLightDirection);
		}

		return true;
	}

	bool DirectionalLightScene::CreateResources()
	{
		/* === Shaders === */
		/* Directional Light */
		AN_CHECK(m_directionalLightShader = GetResources()->CreateShader("assets/shader/directional_light.shader", RenderType::Forward));

		/* === Geometries === */
		/* Quad */
		AN_CHECK(m_rgratGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* Wall VA */
		AN_CHECK(m_rgratVA = m_rgratGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

}
