#include "ansi_timer.h"

namespace AN
{
	constexpr unsigned NanoTickInSecond{ 1000000000 };

	Timer::Timer() :
		m_deltaTime(0.0f),
		m_currentTime(std::chrono::high_resolution_clock::now()),
		m_previousTime(std::chrono::high_resolution_clock::now()),
		m_elapsedTick(0),
		m_startTime(std::chrono::high_resolution_clock::now())
	{

	}

	void Timer::OnUpdate()
	{
		m_currentTime = std::chrono::high_resolution_clock::now();
		m_elapsedTick = m_currentTime - m_previousTime;
		m_previousTime = m_currentTime;
		m_deltaTime = m_elapsedTick.count() / static_cast<float>(NanoTickInSecond);
	}

	void Timer::StartStopwatch()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
	}

	float Timer::GetStopwatchTime() const
	{
		auto checkTime = std::chrono::high_resolution_clock::now();
		auto elapsed = checkTime - m_startTime;
		return elapsed.count() / static_cast<float>(NanoTickInSecond);
	}

}
