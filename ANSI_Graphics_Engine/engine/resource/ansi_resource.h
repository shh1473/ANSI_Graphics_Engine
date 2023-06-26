#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Resource
	{
	public:
		explicit Resource(unsigned resourceId);
		virtual ~Resource();

	protected:
		const unsigned m_resourceId;

	};

}
