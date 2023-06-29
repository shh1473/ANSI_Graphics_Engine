#pragma once

#include "core/ansi_core.h"

namespace AN
{

	class Scene;
	class EventListener;

	class Window
	{
	public:
		explicit Window();
		~Window();

		bool Initialize();
		bool Run();
		void ChangeScene(Scene * scene) { m_nextScene = scene; }

		void AddEventListener(EventListener * listener) { m_eventListeners.push_back(listener); }
		void RemoveEventListener(EventListener * listener) { m_eventListeners.erase(std::remove(m_eventListeners.begin(), m_eventListeners.end(), listener), m_eventListeners.end()); }

		void SetClientSize(float width, float height) { m_clientSize.x = width; m_clientSize.y = height; }
		void SetWindowPosition(int x, int y) { m_windowPosition.x = x; m_windowPosition.y = y; }
		void SetMousePosition(float x, float y) { m_mousePosition.x = x; m_mousePosition.y = y; }

		const glm::vec2 & GetClientSize() const { return m_clientSize; }
		const glm::vec2 & GetMousePosition() const { return m_mousePosition; }
		const std::vector<EventListener *> & GetEventListeners() const { return m_eventListeners; }

	private:
		bool OnRenderGui();
		bool ApplyWindowSettings();
		bool ApplyChangeScene();

		bool m_isGlfwInitialized;
		bool m_isWindowed;
		bool m_isBorderless;
		glm::vec2 m_clientSize;
		glm::vec2 m_mousePosition;
		glm::ivec2 m_windowPosition;
		GLFWwindow * m_window;
		Scene * m_currentScene;
		Scene * m_nextScene;
		std::vector<EventListener *> m_eventListeners;

	};

}