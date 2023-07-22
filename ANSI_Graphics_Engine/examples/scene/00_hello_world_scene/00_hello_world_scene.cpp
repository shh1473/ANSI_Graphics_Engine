#include "00_hello_world_scene.h"

namespace Example
{

	HelloWorldScene::HelloWorldScene()
	{

	}

	bool HelloWorldScene::Initialize()
	{
		AN::Core::GetGui()->SetTitle("00 - Hello World");

		return true;
	}

	bool HelloWorldScene::OnRenderGui()
	{
		ImGui::Text("Hello World!");

		return true;
	}

}
