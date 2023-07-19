#include "02_texture_scene.h"

#include "../examples/shader/texture/texture_shader.h"

namespace Example
{

	TextureScene::TextureScene()
	{

	}

	TextureScene::~TextureScene()
	{
		AN_DELETE(m_orbitControls);
	}

	bool TextureScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle("01 - Color Objects");

		/* === Wall Object === */
		m_wall = AddObject(new AN::Object("Wall"));
		m_wall->GetTransform()->SetScale(8.0f, 8.0f, 8.0f);

		auto wallShader = new TextureShader(m_textureShader, m_wall);
		auto cubeRenderer = m_wall->AddComponent<AN::Renderer>(wallShader);
		cubeRenderer->Input()->SetVertices(m_wallVA->GetId(), m_quadGeometry->GetVertexCount());
		cubeRenderer->Input()->SetIndices(m_quadGeometry->GetIndexBufferId(), m_quadGeometry->GetIndexCount());
		wallShader->SetDiffuseMap(m_wallTexture->GetId());

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		AN::Camera * camera = m_camera->AddComponent<AN::Camera>();
		m_camera->GetTransform()->SetPositionZ(50.0f);
		m_orbitControls = new AN::OrbitControls(camera);

		return true;
	}

	bool TextureScene::OnUpdate()
	{
		return true;
	}

	bool TextureScene::OnRenderGui()
	{
		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return true;
	}

	bool TextureScene::CreateResources()
	{
		/* === Shaders === */
		/* Texture */
		AN_CHECK(m_textureShader = GetResources()->CreateShader("assets/shader/texture.shader", RenderType::Forward));

		/* === Geometries === */
		/* Quad */
		AN_CHECK(m_quadGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_quadGeometry->GenerateBox(2.0f, 2.0f, 2.0f, 1, 1, 1));
		/* Wall VA */
		AN_CHECK(m_wallVA = m_quadGeometry->GenerateVertexArray(AN::POSITION | AN::TEXCOORD));

		/* === Textures === */
		AN_CHECK(m_wallTexture = GetResources()->CreateTexture("assets/texture/gravel_diffuse.jpg"));

		return true;
	}

}
