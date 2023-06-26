#pragma once

#include "common/ansi_common.h"

namespace AN
{
	class Log;
	class Timer;
	class Config;
	class Window;
	class Gui;

	class Core
	{
	public:
		static bool CreateInstance();
		static void DeleteInstance();

		static Core * GetInstance() { return m_Instance; }
		static Log * GetLog() { return m_Instance->m_log; }
		static Timer * GetTimer() { return m_Instance->m_timer; }
		static Config * GetConfig() { return m_Instance->m_config; }
		static Window * GetWindow() { return m_Instance->m_window; }
		static Gui * GetGui() { return m_Instance->m_gui; }

	private:
		explicit Core();
		~Core();

		bool Initialize();

		static Core * m_Instance;

		Log * m_log;
		Timer * m_timer;
		Config * m_config;
		Window * m_window;
		Gui * m_gui;

	};

}
