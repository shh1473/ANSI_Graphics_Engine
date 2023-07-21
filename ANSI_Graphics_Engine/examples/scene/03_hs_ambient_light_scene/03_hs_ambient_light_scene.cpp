#include "03_hs_ambient_light_scene.h"

#include "../examples/shader/hs_ambient_light/hs_ambient_light_shader.h"

namespace Example
{

	const glm::vec3 HSAmbientLightScene::m_DefaultAmbientLightUpColor(1.0f, 0.0f, 0.0f);
	const glm::vec3 HSAmbientLightScene::m_DefaultAmbientLightDownColor(0.0f, 0.0f, 1.0f);

	HSAmbientLightScene::HSAmbientLightScene() :
		m_isWireframe(false),
		m_upColor(m_DefaultAmbientLightUpColor),
		m_downColor(m_DefaultAmbientLightDownColor)
	{

	}

	bool HSAmbientLightScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle("01 - Color Objects");

		/* === Ambient Light === */
		m_ambientLight = AddObject(new AN::Object("Ambient Light"));

		auto ambientLight = m_ambientLight->AddComponent<AN::AmbientLight>(m_DefaultAmbientLightUpColor, m_DefaultAmbientLightDownColor);

		/* === RGRat Object === */
		m_rgrat = AddObject(new AN::Object("Cow"));
		m_rgrat->GetTransform()->SetScale(1.0f, 1.0f, 1.0f);

		auto wallShader = new HemiSphereAmbientLightShader(m_hsAmbientLightShader, m_rgrat, ambientLight);
		auto cubeRenderer = m_rgrat->AddComponent<AN::Renderer>(wallShader);
		cubeRenderer->Input()->SetVertices(m_rgratVA->GetId(), m_rgratGeometry->GetVertexCount());
		cubeRenderer->Input()->SetIndices(m_rgratGeometry->GetIndexBufferId(), m_rgratGeometry->GetIndexCount());

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

		if (ImGui::ColorEdit3("UpColor", &m_upColor.x))
		{
			m_ambientLight->FindComponent<AN::AmbientLight>()->SetUpColor(m_upColor);
		}

		if (ImGui::ColorEdit3("DownColor", &m_downColor.x))
		{
			m_ambientLight->FindComponent<AN::AmbientLight>()->SetDownColor(m_downColor);
		}

		return true;
	}

	bool HSAmbientLightScene::CreateResources()
	{
		/* === Shaders === */
		/* Hemisphere Ambient Light */
		AN_CHECK(m_hsAmbientLightShader = GetResources()->CreateShader("assets/shader/hs_ambient_light.shader", RenderType::Forward));

		/* === Geometries === */
		/* Quad */
		AN_CHECK(m_rgratGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* Wall VA */
		AN_CHECK(m_rgratVA = m_rgratGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

}