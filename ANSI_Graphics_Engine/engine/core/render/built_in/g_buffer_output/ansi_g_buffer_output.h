#pragma once

#include "core/render/output_executor/output_param/ansi_output_param.h"

namespace AN
{

	class GBufferOutput : public OutputParam
	{
	public:
		explicit GBufferOutput();
		virtual ~GBufferOutput();

		bool Initialize();

		unsigned GetDeferredOutputTextureId() const { return m_deferredOutputTextureId; }

	private:
		unsigned m_deferredOutputTextureId;

	};

}
