#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class InputExecutor;

	class DispatchParam
	{
	public:
		friend class InputExecutor;

		explicit DispatchParam();

		void SetSizeX(unsigned size) { m_size.x = size; }
		void SetSizeY(unsigned size) { m_size.y = size; }
		void SetSizeZ(unsigned size) { m_size.z = size; }

	private:
		glm::uvec3 m_size;

	};

}
