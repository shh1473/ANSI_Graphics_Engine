#include "ansi_event_listener.h"

#include "core/window/ansi_window.h"

namespace AN
{

	EventListener::EventListener()
	{
		Core::GetWindow()->AddEventListener(this);
	}

	EventListener::~EventListener()
	{
		Core::GetWindow()->RemoveEventListener(this);
	}

	void EventListener::OnWindowResize()
	{

	}

	void EventListener::OnMouseUp(int button)
	{

	}

	void EventListener::OnMouseDown(int button, const glm::vec2 & position)
	{

	}

	void EventListener::OnMouseMove(const glm::vec2 & position)
	{

	}

	void EventListener::OnMouseWheel(float deltaY)
	{

	}

}
