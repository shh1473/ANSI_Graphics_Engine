#include "hello_world_scene.h"

namespace Example
{

	const std::string HelloWorldScene::m_SceneName{ "Hello World" };

	HelloWorldScene::HelloWorldScene()
	{

	}

	bool HelloWorldScene::Initialize()
	{
		AN::Core::GetGui()->SetTitle(m_SceneName);

		GL_CHECK(glClearDepth(1.0f));
		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		return true;
	}

	bool HelloWorldScene::OnUpdate()
	{
		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		return true;
	}

	bool HelloWorldScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		ImGui::Text("Hello World!");

		return ExampleScene::OnRenderGui();
	}

}
