#pragma once

#include "resource/ansi_resource.h"

namespace AN
{

	class Shader : public Resource
	{
	public:
		explicit Shader(unsigned resourceId);
		virtual ~Shader();

	};

}
