#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{
	
	class HelloWorldScene : public AN::Scene
	{
	public:
		explicit HelloWorldScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		
	};

}
