#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class EventListener
	{
	public:
		explicit EventListener();

		virtual void OnMouseUp(int button);
		virtual void OnMouseDown(int button, const glm::vec2 & position);
		virtual void OnMouseMove(const glm::vec2 & position);
		virtual void OnMouseWheel(float deltaY);

	};

}
