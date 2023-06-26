#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Window
	{
	public:
		explicit Window();
		~Window();

		bool Initialize();
		bool Run();

	private:
		bool m_isGlfwInitialized;
		GLFWwindow * m_window;

	};

}