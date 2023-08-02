#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ExampleManager : public AN::Scene
	{
	public:
		explicit ExampleManager();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;

	private:
		using ExampleSceneRegistry = std::pair<std::string, std::function<AN::Scene * ()>>;

	private:
		std::vector<ExampleSceneRegistry> m_exampleScenes;

	};

}
