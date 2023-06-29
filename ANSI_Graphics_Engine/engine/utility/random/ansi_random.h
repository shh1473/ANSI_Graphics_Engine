#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Random
	{
	public:
		static int Int(int min, int max);
		static float Float(float min = 0.0f, float max = 1.0f);

	private:
		explicit Random() = delete;

		static std::random_device m_Device;
		static std::mt19937_64 m_Engine;

	};

}
