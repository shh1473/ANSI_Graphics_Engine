#include "ansi_config.h"

#include "core/log/ansi_log.h"

namespace AN
{
	const std::string Config::m_IsWindowedKey{ "is_windowed" };
	const std::string Config::m_WindowPositionXKey{ "position_x" };
	const std::string Config::m_WindowPositionYKey{ "position_y" };
	const std::string Config::m_ClientWidthKey{ "client_width" };
	const std::string Config::m_ClientHeightKey{ "client_height" };
	const std::string Config::m_WindowTitleKey{ "title" };
	const std::string Config::m_IsEnableVSyncKey{ "is_enable" };
	const std::string Config::m_SwapIntervalKey{ "swap_interval" };

	Config::Config() :
		XML("configurations/ansi_graphics_engine_config.xml"),
		m_isWindowed(true),
		m_windowPosition(0),
		m_clientSize(1024),
		m_windowTitle("Untitled"),
		m_isEnableVSync(false),
		m_swapInterval(1),
		m_window(nullptr, "window"),
		m_vsync(nullptr, "vsync")
	{

	}

	Config::~Config()
	{
		AN_ERROR_LOG_IF(Save());
	}

	bool Config::Initialize()
	{
		Open();
		PushElement(&m_window);
		PushElement(&m_vsync);
		if (!Load()) { return false; }

		m_isWindowed = m_window.first->BoolAttribute(m_IsWindowedKey.c_str());
		m_windowPosition.x = m_window.first->IntAttribute(m_WindowPositionXKey.c_str());
		m_windowPosition.y = m_window.first->IntAttribute(m_WindowPositionYKey.c_str());
		m_clientSize.x = m_window.first->UnsignedAttribute(m_ClientWidthKey.c_str());
		m_clientSize.y = m_window.first->UnsignedAttribute(m_ClientHeightKey.c_str());
		m_windowTitle = m_window.first->Attribute(m_WindowTitleKey.c_str());

		m_isEnableVSync = m_vsync.first->BoolAttribute(m_IsWindowedKey.c_str());
		m_swapInterval = m_vsync.first->UnsignedAttribute(m_IsWindowedKey.c_str());

		return true;
	}

	bool Config::Save()
	{
		m_window.first->SetAttribute(m_IsWindowedKey.c_str(), m_isWindowed);
		m_window.first->SetAttribute(m_WindowPositionXKey.c_str(), m_windowPosition.x);
		m_window.first->SetAttribute(m_WindowPositionYKey.c_str(), m_windowPosition.y);
		m_window.first->SetAttribute(m_ClientWidthKey.c_str(), m_clientSize.x);
		m_window.first->SetAttribute(m_ClientHeightKey.c_str(), m_clientSize.y);

		m_vsync.first->SetAttribute(m_IsEnableVSyncKey.c_str(), m_isEnableVSync);
		m_vsync.first->SetAttribute(m_SwapIntervalKey.c_str(), m_swapInterval);

		return Apply();
	}

}
