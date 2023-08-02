#include "ansi_window.h"

#include "core/log/ansi_log.h"
#include "core/timer/ansi_timer.h"
#include "core/xml/config/ansi_config.h"
#include "core/render/ansi_render.h"
#include "core/gui/ansi_gui.h"
#include "scene/ansi_scene.h"
#include "utility/converter/ansi_converter.h"
#include "utility/obj_loader/ansi_obj_loader.h"
#include "utility/event_listener/ansi_event_listener.h"

#include "../examples/manager/example_manager.h"

namespace AN
{

	void OnWindowResize(GLFWwindow * window, int width, int height);
	void OnWindowMove(GLFWwindow * window, int positionX, int positionY);
	void OnMouseButton(GLFWwindow * window, int button, int action, int mods);
	void OnMouseMove(GLFWwindow * window, double positionX, double positionY);
	void OnMouseWheel(GLFWwindow * window, double deltaX, double deltaY);

	Window::Window() :
		m_isGlfwInitialized(false),
		m_isWindowed(false),
		m_isBorderless(false),
		m_clientSize(1024.0f),
		m_mousePosition(0.0f),
		m_windowPosition(0),
		m_window(nullptr),
		m_currentScene(nullptr),
		m_nextScene(nullptr),
		m_eventListeners()
	{

	}

	Window::~Window()
	{
		AN_DELETE(m_currentScene);
		glfwGetWindowPos(m_window, &m_windowPosition.x, &m_windowPosition.y);
		Core::GetConfig()->SetIsWindowed(m_isWindowed);
		Core::GetConfig()->SetWindowPosition(m_windowPosition);
		Core::GetConfig()->SetClientSize(m_clientSize);
		if (m_isGlfwInitialized) { glfwTerminate(); }
	}

	bool Window::Initialize()
	{
		m_isWindowed = Core::GetConfig()->GetIsWindowed();
		m_clientSize.x = static_cast<float>(Core::GetConfig()->GetClientSize().x);
		m_clientSize.y = static_cast<float>(Core::GetConfig()->GetClientSize().y);
		m_windowPosition = Core::GetConfig()->GetWindowPosition();

		/* GLFW 초기화 및 버전 확인 */
		AN_CHECK_LOG(glfwInit());
		Core::GetLog()->WriteLine(L"GLFW Version: " + Converter::ToUnicode(glfwGetVersionString()));
		m_isGlfwInitialized = true;

		/* Window 생성 */
		m_window = glfwCreateWindow(
			static_cast<int>(m_clientSize.x),
			static_cast<int>(m_clientSize.y),
			Core::GetConfig()->GetWindowTitle().c_str(), nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			AN_CHECK_LOG(m_window);
		}
		GLFW_CHECK(glfwSetWindowPos(m_window, m_windowPosition.x, m_windowPosition.y));
		GLFW_CHECK(glfwMakeContextCurrent(m_window));
		GLFW_CHECK(glfwSwapInterval(Core::GetConfig()->GetIsEnableVSync() ? Core::GetConfig()->GetSwapInterval() : 0));

		/* GLEW 초기화 및 버전 확인 */
		GLenum result{ glewInit() };
		AN_CHECK_LOG_M(result == GLEW_OK, Converter::ToUnicode(glewGetErrorString(result)));
		Core::GetLog()->WriteLine(L"GLEW Version: " + Converter::ToUnicode(glewGetString(GLEW_VERSION)));

		/* OpenGL 버전 확인 */
		Core::GetLog()->WriteLine(L"OpenGL Version: " + Converter::ToUnicode(glGetString(GL_VERSION)));

		/* 이벤트 콜백 설정 */
		glfwSetWindowSizeCallback(m_window, OnWindowResize);
		glfwSetWindowPosCallback(m_window, OnWindowMove);
		glfwSetMouseButtonCallback(m_window, OnMouseButton);
		glfwSetCursorPosCallback(m_window, OnMouseMove);
		glfwSetScrollCallback(m_window, OnMouseWheel);

		return true;
	}

	bool Window::Run()
	{
		m_nextScene = new Example::ExampleManager();
		AN_CHECK(ApplyChangeScene());

		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GL_CHECK(glClearDepth(1.0));

		while (!glfwWindowShouldClose(m_window))
		{
			Core::GetTimer()->OnUpdate();
			AN_CHECK(m_currentScene->OnDefaultUpdate());
			AN_CHECK(m_currentScene->OnUpdate());
			AN_CHECK(m_currentScene->OnDefaultLateUpdate());
			AN_CHECK(m_currentScene->OnLateUpdate());

			AN_CHECK(Core::GetRender()->OnRender());

			if (Core::GetGui()->OnRenderBegin())
			{
				AN_CHECK(m_currentScene->OnRenderGui());
				AN_CHECK(OnRenderGui());
			}
			Core::GetGui()->OnRenderEnd();

			GLFW_CHECK(glfwSwapBuffers(m_window));
			GLFW_CHECK(glfwPollEvents());

			if (m_nextScene) { AN_CHECK(ApplyChangeScene()); }
		}

		return true;
	}

	bool Window::OnRenderGui()
	{
		ImGui::Text(">--------- Window Settings ---------<");

		ImGui::Checkbox("Windowed", &m_isWindowed);
		if (m_isWindowed) {
			ImGui::Checkbox("Borderless", &m_isBorderless);
			if (!m_isBorderless) { ImGui::InputFloat2("Resolution", &m_clientSize[0]); }
		}

		if (ImGui::Button("Apply")) { AN_CHECK(ApplyWindowSettings()); }

		return true;
	}

	bool Window::ApplyWindowSettings()
	{
		GLFWmonitor * monitor{ glfwGetPrimaryMonitor() };
		const GLFWvidmode * mode{ glfwGetVideoMode(monitor) };

		if (m_isWindowed)
		{
			if (m_isBorderless)
			{
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, 0, 0,
					mode->width, mode->height, mode->refreshRate));
			}
			else
			{
				m_windowPosition.x = glm::max(m_windowPosition.x, 50);
				m_windowPosition.y = glm::max(m_windowPosition.y, 50);
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, m_windowPosition.x, m_windowPosition.y,
					static_cast<int>(m_clientSize.x), static_cast<int>(m_clientSize.y), mode->refreshRate));
			}
		}
		else
		{
			GLFW_CHECK(glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate));
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

		Core::GetRender()->Reset();

		return true;
	}

	void OnWindowResize(GLFWwindow * window, int width, int height)
	{
		Core::GetWindow()->SetClientSize(static_cast<float>(width), static_cast<float>(height));
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnWindowResize(); }
	}

	void OnWindowMove(GLFWwindow * window, int positionX, int positionY)
	{
		Core::GetWindow()->SetWindowPosition(positionX, positionY);
	}

	void OnMouseButton(GLFWwindow * window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseDown(button, Core::GetWindow()->GetMousePosition()); }
		}
		else
		{
			for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseUp(button); }
		}
	}

	void OnMouseMove(GLFWwindow * window, double positionX, double positionY)
	{
		Core::GetWindow()->SetMousePosition(static_cast<float>(positionX), static_cast<float>(positionY));
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseMove(Core::GetWindow()->GetMousePosition()); }
	}

	void OnMouseWheel(GLFWwindow * window, double deltaX, double deltaY)
	{
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseWheel(static_cast<float>(deltaY)); }
	}

}