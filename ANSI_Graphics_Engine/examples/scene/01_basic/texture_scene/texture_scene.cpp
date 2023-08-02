#include "texture_scene.h"

#include "material/texture/texture_material.h"

namespace Example
{

	const std::string TextureScene::m_SceneName{ "Texture" };

	TextureScene::TextureScene()
	{

	}

	bool TextureScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Wall Object === */
		m_wall = AddObject(new AN::Object("Wall"));
		m_wall->GetTransform()->SetScale(8.0f, 8.0f, 8.0f);

		auto wallMaterial = new TextureMaterial(m_textureShader);
		wallMaterial->SetDiffuseMap(m_wallTexture->GetId());
		m_wall->AddComponent<AN::Renderer>(m_wallVA, wallMaterial);

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto * camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool TextureScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return ExampleScene::OnRenderGui();
	}

	bool TextureScene::CreateResources()
	{
		/* === Shader === */
		/* Texture */
		AN_CHECK(m_textureShader = GetResources()->CreateShader("assets/shader/texture.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* Plane */
		auto planeGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(planeGeometry->GeneratePlane(2.0f, 2.0f));

		/* Plane VA */
		AN_CHECK(m_wallVA = planeGeometry->GenerateVertexArray(AN::TEXCOORD));

		/* === Texture === */
		AN_CHECK(m_wallTexture = GetResources()->CreateTexture("assets/texture/gravel_diffuse.jpg"));

		return true;
	}

}
