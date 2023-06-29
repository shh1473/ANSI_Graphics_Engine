#include "ansi_random.h"

namespace AN
{

	std::random_device Random::m_Device{};
	std::mt19937_64 Random::m_Engine{ m_Device() };

	int Random::Int(int min, int max)
	{
		std::uniform_int<int> range(min, max);
		return range(m_Engine);
	}

	float Random::Float(float min, float max)
	{
		std::uniform_real<float> range(min, max);
		return range(m_Engine);
	}

}
