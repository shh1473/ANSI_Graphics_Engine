#include "02_texture_scene.h"

#include "../examples/shader/texture/texture_shader.h"

namespace Example
{

	const std::string TextureScene::m_SceneName{ "02 - Texture" };

	TextureScene::TextureScene() :
		m_isWireframe(false)
	{

	}

	bool TextureScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Wall Object === */
		m_wall = AddObject(new AN::Object("Wall"));
		m_wall->GetTransform()->SetScale(8.0f, 8.0f, 8.0f);

		auto wallShader = new TextureShader(m_textureShader, m_wall);
		auto cubeRenderer = m_wall->AddComponent<AN::Renderer>(wallShader);
		cubeRenderer->Input()->SetVertices(m_wallVA->GetId(), m_planeGeometry->GetVertexCount());
		cubeRenderer->Input()->SetIndices(m_planeGeometry->GetIndexBufferId(), m_planeGeometry->GetIndexCount());
		wallShader->SetDiffuseMap(m_wallTexture->GetId());

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		AN::Camera * camera = m_camera->AddComponent<AN::Camera>();
		camera->Raster()->SetCullMode(AN::CullMode::None);
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool TextureScene::OnUpdate()
	{
		return true;
	}

	bool TextureScene::OnRenderGui()
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

		return ExampleScene::OnRenderGui();
	}

	bool TextureScene::CreateResources()
	{
		/* === Shaders === */
		/* Texture */
		AN_CHECK(m_textureShader = GetResources()->CreateShader("assets/shader/texture.shader", RenderType::Forward));

		/* === Geometries === */
		/* Plane */
		AN_CHECK(m_planeGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_planeGeometry->GeneratePlane(2.0f, 2.0f));
		/* Plane VA */
		AN_CHECK(m_wallVA = m_planeGeometry->GenerateVertexArray(AN::TEXCOORD));

		/* === Textures === */
		AN_CHECK(m_wallTexture = GetResources()->CreateTexture("assets/texture/gravel_diffuse.jpg"));

		return true;
	}

}
