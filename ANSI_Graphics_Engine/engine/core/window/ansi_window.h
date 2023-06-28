#pragma once

#include "core/ansi_core.h"

namespace AN
{

	class Scene;

	class Window
	{
	public:
		explicit Window();
		~Window();

		bool Initialize();
		bool Run();
		void ChangeScene(Scene * scene) { m_nextScene = scene; }

	private:
		bool ApplyChangeScene();

		bool m_isGlfwInitialized;
		GLFWwindow * m_window;
		Scene * m_currentScene;
		Scene * m_nextScene;

	};

}