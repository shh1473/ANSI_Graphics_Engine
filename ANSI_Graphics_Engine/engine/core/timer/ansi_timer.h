#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Timer
	{
	public:
		explicit Timer();

		void OnUpdate();

		float GetDeltaTime() const { return m_deltaTime; }

	private:
		float m_deltaTime;
		std::chrono::steady_clock::time_point m_currentTime;
		std::chrono::steady_clock::time_point m_previousTime;
		std::chrono::nanoseconds m_elapsedTick;

	};

}
