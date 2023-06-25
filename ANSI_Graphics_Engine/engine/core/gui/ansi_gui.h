#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "common/ansi_common.h"

namespace AN
{
	class Gui
	{
	public:
		explicit Gui();
		~Gui();

		bool Initialize();

		bool OnRender();

	private:
		bool m_isCreatedContext;
		bool m_isInitializedGlfw;
		bool m_isInitializedOpenGL;
		std::string m_title;

	};

}
