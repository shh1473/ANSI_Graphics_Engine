#include "ansi_window.h"

#include "core/log/ansi_log.h"
#include "core/timer/ansi_timer.h"
#include "core/xml/config/ansi_config.h"
#include "core/render/ansi_render.h"
#include "core/gui/ansi_gui.h"
#include "scene/ansi_scene.h"
#include "utility/converter/ansi_converter.h"
#include "utility/obj_loader/ansi_obj_loader.h"

//#include "../examples/scene/00_hello_world_scene/00_hello_world_scene.h"
#include "../examples/scene/01_color_cube_scene/01_color_cube_scene.h"

namespace AN
{

	Window::Window() :
		m_isGlfwInitialized(false),
		m_window(nullptr),
		m_currentScene(nullptr),
		m_nextScene(nullptr)
	{

	}

	Window::~Window()
	{
		AN_DELETE(m_currentScene);
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
		m_nextScene = new Example::ColorCubeScene();
		AN_CHECK(ApplyChangeScene());

		while (!glfwWindowShouldClose(m_window))
		{
			Core::GetTimer()->OnUpdate();
			m_currentScene->OnDefaultUpdate();
			m_currentScene->OnUpdate();
			m_currentScene->OnDefaultLateUpdate();
			m_currentScene->OnLateUpdate();

			GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

			Core::GetRender()->OnRender();
			Core::GetGui()->OnRenderBegin();
			m_currentScene->OnRenderGui();
			Core::GetGui()->OnRenderEnd();

			GL_CHECK(glfwSwapBuffers(m_window));
			GL_CHECK(glfwPollEvents());

			if (m_nextScene) { AN_CHECK(ApplyChangeScene()); }
		}

		return true;
	}

	bool Window::ApplyChangeScene()
	{
		AN_DELETE(m_currentScene);
		m_currentScene = m_nextScene;
		m_nextScene = nullptr;
		AN_CHECK(m_currentScene->CreateResources());
		AN_CHECK(m_currentScene->Initialize());

		return true;
	}

}