#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{
	
	class HelloWorldScene : public ExampleScene
	{
	public:
		explicit HelloWorldScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;

	public:
		static const std::string m_SceneName;
		
	};

}
