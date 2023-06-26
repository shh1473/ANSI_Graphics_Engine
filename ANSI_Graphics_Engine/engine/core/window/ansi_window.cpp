#include "ansi_window.h"

#include "core/ansi_core.h"
#include "core/log/ansi_log.h"
#include "core/timer/ansi_timer.h"
#include "core/xml/config/ansi_config.h"
#include "core/gui/ansi_gui.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	Window::Window() :
		m_isGlfwInitialized(false),
		m_window(nullptr)
	{

	}

	Window::~Window()
	{
		if (m_isGlfwInitialized) { glfwTerminate(); }
	}

	bool Window::Initialize()
	{
		/* GLFW 초기화 및 버전 확인 */
		AN_CHECK_LOG(glfwInit());
		Core::GetLog()->WriteLine(L"GLFW Version: " + Converter::ToUnicode(glfwGetVersionString()));
		m_isGlfwInitialized = true;

		/* Window 생성 */
		m_window = glfwCreateWindow(
			Core::GetConfig()->GetClientWidth(),
			Core::GetConfig()->GetClientHeight(),
			Core::GetConfig()->GetWindowTitle().c_str(),
			nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			AN_CHECK_LOG(m_window);
		}
		GL_CHECK(glfwMakeContextCurrent(m_window));
		GL_CHECK(glfwSwapInterval(Core::GetConfig()->GetIsEnableVSync() ? Core::GetConfig()->GetSwapInterval() : 0));

		/* GLEW 초기화 및 버전 확인 */
		GLenum result{ glewInit() };
		AN_CHECK_LOG_M(result == GLEW_OK, Converter::ToUnicode(glewGetErrorString(result)));
		Core::GetLog()->WriteLine(L"GLEW Version: " + Converter::ToUnicode(glewGetString(GLEW_VERSION)));

		/* OpenGL 버전 확인 */
		Core::GetLog()->WriteLine(L"OpenGL Version: " + Converter::ToUnicode(glGetString(GL_VERSION)));

		return true;
	}

	bool Window::Run()
	{
		while (!glfwWindowShouldClose(m_window))
		{
			Core::GetTimer()->OnUpdate();

			GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

			Core::GetGui()->OnRender();

			GL_CHECK(glfwSwapBuffers(m_window));
			GL_CHECK(glfwPollEvents());
		}

		return true;
	}

}