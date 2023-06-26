#include "ansi_timer.h"

namespace AN
{
	constexpr unsigned NanoTickInSecond{ 1000000000 };

	Timer::Timer() :
		m_deltaTime(0.0f),
		m_currentTime(std::chrono::high_resolution_clock::now()),
		m_previousTime(std::chrono::high_resolution_clock::now()),
		m_elapsedTick(0)
	{

	}

	void Timer::OnUpdate()
	{
		m_currentTime = std::chrono::high_resolution_clock::now();
		m_elapsedTick = m_currentTime - m_previousTime;
		m_previousTime = m_currentTime;
		m_deltaTime = m_elapsedTick.count() / static_cast<float>(NanoTickInSecond);
	}

}
