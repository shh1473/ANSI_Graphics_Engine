#include "example_manager.h"

#include "../scene/00_hello_world_scene/00_hello_world_scene.h"
#include "../scene/01_colors_scene/01_colors_scene.h"
#include "../scene/02_texture_scene/02_texture_scene.h"
#include "../scene/03_hs_ambient_light_scene/03_hs_ambient_light_scene.h"
#include "../scene/04_directional_light_scene/04_directional_light_scene.h"
#include "../scene/05_point_lights_scene/05_point_lights_scene.h"
#include "../scene/06_capsule_lights_scene/06_capsule_lights_scene.h"

namespace Example
{

	ExampleManager::ExampleManager() :
		m_exampleScenes()
	{

	}

	bool ExampleManager::Initialize()
	{
		AN::Core::GetGui()->SetTitle("Example Manager");

		m_exampleScenes.push_back(std::make_pair(HelloWorldScene::m_SceneName, []() { return new HelloWorldScene(); }));
		m_exampleScenes.push_back(std::make_pair(ColorsScene::m_SceneName, []() { return new ColorsScene(); }));
		m_exampleScenes.push_back(std::make_pair(TextureScene::m_SceneName, []() { return new TextureScene(); }));
		m_exampleScenes.push_back(std::make_pair(HSAmbientLightScene::m_SceneName, []() { return new HSAmbientLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(DirectionalLightScene::m_SceneName, []() { return new DirectionalLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(PointLightsScene::m_SceneName, []() { return new PointLightsScene(); }));
		m_exampleScenes.push_back(std::make_pair(CapsuleLightsScene::m_SceneName, []() { return new CapsuleLightsScene(); }));

		GL_CHECK(glClearDepth(1.0f));
		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		return true;
	}

	bool ExampleManager::OnRenderGui()
	{
		ImGui::Text(">---------- Example List -----------<");

		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		for (unsigned i{ 0 }; i < m_exampleScenes.size(); ++i)
		{
			if (ImGui::Button(m_exampleScenes[i].first.c_str()))
			{
				AN::Core::GetWindow()->ChangeScene(m_exampleScenes[i].second());
			}
		}

		ImGui::NewLine();

		return true;
	}

}
