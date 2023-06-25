#pragma once

#include "core/xml/ansi_xml.h"

namespace AN
{

	class Config : public XML
	{
	public:
		explicit Config();

		bool Initialize();
		bool Save();

		void SetIsWindowed(bool isWindowed) { m_isWindowed = isWindowed; }
		void SetWindowPositionX(unsigned windowPositionX) { m_windowPositionX = windowPositionX; }
		void SetWindowPositionY(unsigned windowPositionY) { m_windowPositionY = windowPositionY; }
		void SetClientWidth(unsigned clientWidth) { m_clientWidth = clientWidth; }
		void SetClientHeight(unsigned clientHeight) { m_clientHeight = clientHeight; }

		void SetIsEnableVSync(bool isEnableVSync) { m_isEnableVSync = isEnableVSync; }
		void SetSwapInterval(unsigned swapInterval) { m_swapInterval = swapInterval; }

		bool GetIsWindowed() const { return m_isWindowed; }
		unsigned GetWindowPositionX() const { return m_windowPositionX; }
		unsigned GetWindowPositionY() const { return m_windowPositionY; }
		unsigned GetClientWidth() const { return m_clientWidth; }
		unsigned GetClientHeight() const { return m_clientHeight; }
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
		unsigned m_windowPositionX;
		unsigned m_windowPositionY;
		unsigned m_clientWidth;
		unsigned m_clientHeight;
		std::string m_windowTitle;

		// VSync
		bool m_isEnableVSync;
		unsigned m_swapInterval;

		// Elements
		ElementPair m_window;
		ElementPair m_vsync;

	};

}
