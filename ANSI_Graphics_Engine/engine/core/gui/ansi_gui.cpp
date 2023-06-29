#include "ansi_gui.h"

#include "core/ansi_core.h"
#include "core/log/ansi_log.h"

namespace AN
{

	Gui::Gui() :
		m_isCreatedContext(false),
		m_isInitializedGlfw(false),
		m_isInitializedOpenGL(false),
		m_isWindowHovered(false),
		m_title("Scene Selection")
	{

	}

	Gui::~Gui()
	{
		if (m_isInitializedOpenGL) { ImGui_ImplOpenGL3_Shutdown(); }
		if (m_isInitializedGlfw) { ImGui_ImplGlfw_Shutdown(); }
		if (m_isCreatedContext) { ImGui::DestroyContext(); }
	}

	bool Gui::Initialize()
	{
		AN_CHECK_LOG(IMGUI_CHECKVERSION());
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		m_isCreatedContext = true;

		AN_CHECK_LOG(ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true));
		m_isInitializedGlfw = true;

		AN_CHECK_LOG(ImGui_ImplOpenGL3_Init("#version 330"));
		m_isInitializedOpenGL = true;

		return true;
	}

	bool Gui::OnRenderBegin()
	{
		static bool isShow{ false };

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		isShow = ImGui::Begin(m_title.c_str());
		m_isWindowHovered = ImGui::IsWindowHovered();

		return isShow;
	}

	void Gui::OnRenderEnd()
	{
		ImGui::Text("%.3f ms / %d FPS", 1000.0f / ImGui::GetIO().Framerate, static_cast<unsigned>(ImGui::GetIO().Framerate));

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}
