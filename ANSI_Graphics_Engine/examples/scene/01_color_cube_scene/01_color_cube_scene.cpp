#include "01_color_cube_scene.h"

#include "../examples/shader/color/color_shader.h"

namespace Example
{

	ColorCubeScene::ColorCubeScene()
	{

	}

	ColorCubeScene::~ColorCubeScene()
	{

	}

	bool ColorCubeScene::Initialize()
	{
		AN::Core::GetGui()->SetTitle("01 - Color Cube");

		m_cube = AddObject(new AN::Object("Cube"));
		AN::Renderer * cubeRenderer = m_cube->AddComponent<AN::Renderer>(new ColorShader(m_colorShader, m_cube));
		cubeRenderer->Input()->SetVertices(m_cubeVA->GetId(), m_cubeGeometry->GetVertexCount());

		m_camera = AddObject(new AN::Object("Camera"));
		AN::Camera * camera = m_camera->AddComponent<AN::Camera>();
		camera->SetSize(AN::Core::GetConfig()->GetClientWidth(), AN::Core::GetConfig()->GetClientHeight());
		m_camera->GetTransform()->SetPositionZ(25.0f);

		return true;
	}

	bool ColorCubeScene::OnRenderGui()
	{
		ImGui::Text("%.3f ms / %d FPS", 1000.0f / ImGui::GetIO().Framerate, static_cast<unsigned>(ImGui::GetIO().Framerate));

		return true;
	}

	bool ColorCubeScene::CreateResources()
	{
		m_colorShader = GetResources()->CreateShader("assets/shader/color.shader", RenderType::Forward);
		m_cubeGeometry = GetResources()->CreateGeometry();
		m_cubeGeometry->LoadFromObj("assets/model/rgpose.obj", false);
		m_cubeVA = m_cubeGeometry->GenerateVertexArray();

		return true;
	}

}
