#pragma once

#include "core/ansi_core.h"

#define AN_DT AN::Core::GetTimer()->GetDeltaTime()

namespace AN
{

	class Timer
	{
	public:
		explicit Timer();

		void OnUpdate();
		void StartStopwatch();

		float GetDeltaTime() const { return m_deltaTime; }
		float GetStopwatchTime() const;

	private:
		float m_deltaTime;
		std::chrono::steady_clock::time_point m_currentTime;
		std::chrono::steady_clock::time_point m_previousTime;
		std::chrono::nanoseconds m_elapsedTick;

		std::chrono::steady_clock::time_point m_startTime;

	};

}
