#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "core/ansi_core.h"

namespace AN
{

	class Gui
	{
	public:
		explicit Gui();
		~Gui();

		bool Initialize();
		bool OnRenderBegin();
		void OnRenderEnd();

		void SetTitle(const std::string & title) { m_title = title; }

		bool GetIsWindowHovered() const { return m_isWindowHovered; }

	private:
		bool m_isCreatedContext;
		bool m_isInitializedGlfw;
		bool m_isInitializedOpenGL;
		bool m_isWindowHovered;
		std::string m_title;

	};

}
