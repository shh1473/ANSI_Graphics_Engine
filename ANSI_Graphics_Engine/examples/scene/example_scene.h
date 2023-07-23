#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ExampleScene : public AN::Scene
	{
	public:
		explicit ExampleScene();

		bool OnRenderGui() override;

	};

}
