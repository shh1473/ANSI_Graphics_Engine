#include "03_hs_ambient_light_scene.h"

#include "../examples/shader/hs_ambient_light/hs_ambient_light_shader.h"

namespace Example
{

	const glm::vec3 HSAmbientLightScene::m_DefaultAmbientLightUpColor{ 1.0f, 0.0f, 0.0f };
	const glm::vec3 HSAmbientLightScene::m_DefaultAmbientLightDownColor{ 0.0f, 0.0f, 1.0f };

	HSAmbientLightScene::HSAmbientLightScene() :
		m_isWireframe(false),
		m_ambientLightUpColor(m_DefaultAmbientLightUpColor),
		m_ambientLightDownColor(m_DefaultAmbientLightDownColor)
	{

	}

	bool HSAmbientLightScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle("03 - Hemisphere Ambient Light");

		/* === Ambient Light === */
		m_ambientLight = AddObject(new AN::Object("Ambient Light"));

		auto ambientLight = m_ambientLight->AddComponent<AN::AmbientLight>(m_DefaultAmbientLightUpColor, m_DefaultAmbientLightDownColor);

		/* === RGRat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto hsAmbientLightShader = new HemiSphereAmbientLightShader(m_hsAmbientLightShader, m_rgrat, ambientLight);
		auto rgratRenderer = m_rgrat->AddComponent<AN::Renderer>(hsAmbientLightShader);
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

	bool HSAmbientLightScene::OnUpdate()
	{
		return true;
	}

	bool HSAmbientLightScene::OnRenderGui()
	{
		if (ImGui::Checkbox("Wireframe", &m_isWireframe))
		{
			m_camera->FindComponent<AN::Camera>()->Raster()->SetFillMode((m_isWireframe) ? AN::FillMode::Line : AN::FillMode::Fill);
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		if (ImGui::ColorEdit3("UpColor", &m_ambientLightUpColor.x))
		{
			m_ambientLight->FindComponent<AN::AmbientLight>()->SetUpColor(m_ambientLightUpColor);
		}

		if (ImGui::ColorEdit3("DownColor", &m_ambientLightDownColor.x))
		{
			m_ambientLight->FindComponent<AN::AmbientLight>()->SetDownColor(m_ambientLightDownColor);
		}

		return true;
	}

	bool HSAmbientLightScene::CreateResources()
	{
		/* === Shaders === */
		/* Hemisphere Ambient Light */
		AN_CHECK(m_hsAmbientLightShader = GetResources()->CreateShader("assets/shader/hs_ambient_light.shader", RenderType::Forward));

		/* === Geometries === */
		/* RG Rat */
		AN_CHECK(m_rgratGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* RG Rat VA */
		AN_CHECK(m_rgratVA = m_rgratGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

}
