#pragma once

#include "core/xml/ansi_xml.h"

namespace AN
{

	class Config : public XML
	{
	public:
		explicit Config();
		virtual ~Config();

		bool Initialize();
		bool Save();

		void SetIsWindowed(bool isWindowed) { m_isWindowed = isWindowed; }
		void SetWindowPosition(const glm::ivec2 & position) { m_windowPosition = position; }
		void SetClientSize(const glm::uvec2 & size) { m_clientSize = size; }

		void SetIsEnableVSync(bool isEnableVSync) { m_isEnableVSync = isEnableVSync; }
		void SetSwapInterval(unsigned swapInterval) { m_swapInterval = swapInterval; }

		bool GetIsWindowed() const { return m_isWindowed; }
		const glm::ivec2 & GetWindowPosition() const { return m_windowPosition; }
		const glm::uvec2 & GetClientSize() const { return m_clientSize; }
		const std::string & GetWindowTitle() const { return m_windowTitle; }

		bool GetIsEnableVSync() const { return m_isEnableVSync; }
		unsigned GetSwapInterval() const { return m_swapInterval; }

	private:
		static const std::string m_IsWindowedKey;
		static const std::string m_WindowPositionXKey;
		static const std::string m_WindowPositionYKey;
		static const std::string m_ClientWidthKey;
		static const std::string m_ClientHeightKey;
		static const std::string m_WindowTitleKey;
		static const std::string m_IsEnableVSyncKey;
		static const std::string m_SwapIntervalKey;

		// Window
		bool m_isWindowed;
		glm::ivec2 m_windowPosition;
		glm::uvec2 m_clientSize;
		std::string m_windowTitle;

		// VSync
		bool m_isEnableVSync;
		unsigned m_swapInterval;

		// Elements
		ElementPair m_window;
		ElementPair m_vsync;

	};

}
