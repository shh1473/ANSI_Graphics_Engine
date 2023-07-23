#include "example_scene.h"

#include "../manager/example_manager.h"

namespace Example
{

	ExampleScene::ExampleScene()
	{

	}

	bool ExampleScene::OnRenderGui()
	{
		ImGui::NewLine();
		ImGui::Text(">---------- Miscellaneous ----------<");
		ImGui::Text("%.3f ms / %d FPS", 1000.0f / ImGui::GetIO().Framerate, static_cast<unsigned>(ImGui::GetIO().Framerate));

		if (ImGui::Button("Back to menu"))
		{
			AN::Core::GetWindow()->ChangeScene(new ExampleManager());
		}

		ImGui::NewLine();

		return true;
	}

}
