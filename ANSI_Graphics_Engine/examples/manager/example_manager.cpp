#include "example_manager.h"

#include "../scene/01_basic/hello_world_scene/hello_world_scene.h"
#include "../scene/01_basic/color_scene/color_scene.h"
#include "../scene/01_basic/texture_scene/texture_scene.h"

#include "../scene/02_forward_shading/hs_ambient_light_scene/hs_ambient_light_scene.h"
#include "../scene/02_forward_shading/directional_light_scene/directional_light_scene.h"
#include "../scene/02_forward_shading/point_lights_scene/point_lights_scene.h"
#include "../scene/02_forward_shading/capsule_lights_scene/capsule_lights_scene.h"
#include "../scene/02_forward_shading/spot_lights_scene/spot_lights_scene.h"
#include "../scene/02_forward_shading/spot_shadows_scene/spot_shadows_scene.h"

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
		m_exampleScenes.push_back(std::make_pair(ColorScene::m_SceneName, []() { return new ColorScene(); }));
		m_exampleScenes.push_back(std::make_pair(TextureScene::m_SceneName, []() { return new TextureScene(); }));
		m_exampleScenes.push_back(std::make_pair(HSAmbientLightScene::m_SceneName, []() { return new HSAmbientLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(DirectionalLightScene::m_SceneName, []() { return new DirectionalLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(PointLightsScene::m_SceneName, []() { return new PointLightsScene(); }));
		m_exampleScenes.push_back(std::make_pair(CapsuleLightsScene::m_SceneName, []() { return new CapsuleLightsScene(); }));
		m_exampleScenes.push_back(std::make_pair(SpotLightsScene::m_SceneName, []() { return new SpotLightsScene(); }));
		m_exampleScenes.push_back(std::make_pair(SpotShadowsScene::m_SceneName, []() { return new SpotShadowsScene(); }));

		GL_CHECK(glClearDepth(1.0f));
		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		return true;
	}

	bool ExampleManager::OnUpdate()
	{
		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		return true;
	}

	bool ExampleManager::OnRenderGui()
	{
		ImGui::Text(">---------- Example List -----------<");

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
