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

		bool Initialize(unsigned width, unsigned height);
		bool Run();
		void ChangeScene(Scene * scene) { m_nextScene = scene; }

		void AddEventListener(EventListener * listener) { m_eventListeners.push_back(listener); }
		void RemoveEventListener(EventListener * listener) { m_eventListeners.erase(std::remove(m_eventListeners.begin(), m_eventListeners.end(), listener), m_eventListeners.end()); }

		void SetMousePosition(float x, float y) { m_mousePosition.x = x; m_mousePosition.y = y; }

		float GetWidth() const { return m_width; }
		float GetHeight() const { return m_height; }
		const glm::vec2 & GetMousePosition() const { return m_mousePosition; }
		const std::vector<EventListener *> & GetEventListeners() const { return m_eventListeners; }

	private:
		bool ApplyChangeScene();

		bool m_isGlfwInitialized;
		float m_width;
		float m_height;
		glm::vec2 m_mousePosition;
		GLFWwindow * m_window;
		Scene * m_currentScene;
		Scene * m_nextScene;
		std::vector<EventListener *> m_eventListeners;

	};

}