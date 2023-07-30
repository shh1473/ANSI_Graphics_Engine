#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace AN
{

	class OutputExecutor;

	class OutputParam
	{
	public:
		friend class OutputExecutor;

		explicit OutputParam();

		void SetClearStencil(int clearStencil) { m_clearStencil = clearStencil; }
		void SetClearDepth(float clearDepth) { m_clearDepth = clearDepth; }
		void SetClearColor(const glm::vec4 & clearColor) { m_clearColor = clearColor; }
		void SetMsaa(MSAA msaa) { m_msaa = msaa; }
		void SetFrameBufferId(unsigned frameBufferId) { m_frameBufferId = frameBufferId; }

	private:
		static const int m_DefaultClearStencil;
		static const float m_DefaultClearDepth;
		static const glm::vec4 m_DefaultClearColor;
		static const MSAA m_DefaultMsaa;

	private:
		int m_clearStencil;
		float m_clearDepth;
		glm::vec4 m_clearColor;
		MSAA m_msaa;
		unsigned m_frameBufferId;

	};

}
