#include "hs_ambient_light_scene.h"

#include "material/hs_ambient_light/hs_ambient_light_material.h"

namespace Example
{

	const std::string HSAmbientLightScene::m_SceneName{ "Hemisphere Ambient Light" };

	HSAmbientLightScene::HSAmbientLightScene() :
		m_ambientLightUpColor(1.0f, 0.0f, 0.0f),
		m_ambientLightDownColor(0.0f, 0.0f, 1.0f)
	{

	}

	bool HSAmbientLightScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Ambient Light Object === */
		m_ambientLight = AddObject(new AN::Object("Ambient Light"));

		auto ambientLight = m_ambientLight->AddComponent<AN::HSAmbientLight>(m_ambientLightUpColor, m_ambientLightDownColor);

		/* === RGRat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		m_rgrat->AddComponent<AN::Renderer>(m_rgratVA, new HSAmbientLightMaterial(m_hsAmbientLightShader, ambientLight));

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool HSAmbientLightScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::ColorEdit3("UpColor", &m_ambientLightUpColor.x))
		{
			m_ambientLight->FindComponent<AN::HSAmbientLight>()->SetUpColor(m_ambientLightUpColor);
		}

		if (ImGui::ColorEdit3("DownColor", &m_ambientLightDownColor.x))
		{
			m_ambientLight->FindComponent<AN::HSAmbientLight>()->SetDownColor(m_ambientLightDownColor);
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return ExampleScene::OnRenderGui();
	}

	bool HSAmbientLightScene::CreateResources()
	{
		/* === Shader === */
		/* Hemisphere Ambient Light */
		AN_CHECK(m_hsAmbientLightShader = GetResources()->CreateShader("assets/shader/hs_ambient_light.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* RG Rat */
		auto rgratGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));

		/* RG Rat VA */
		AN_CHECK(m_rgratVA = rgratGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

}
