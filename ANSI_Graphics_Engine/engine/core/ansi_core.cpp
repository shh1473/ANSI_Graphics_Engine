#include "ansi_core.h"

#include "log/ansi_log.h"
#include "xml/config/ansi_config.h"
#include "window/ansi_window.h"
#include "gui/ansi_gui.h"

namespace AN
{
	Core * Core::m_Instance{ nullptr };

	bool Core::CreateInstance()
	{
		m_Instance = new Core();
		AN_CHECK(m_Instance->Initialize());

		return true;
	}

	void Core::DeleteInstance()
	{
		AN_DELETE(m_Instance);
	}

	Core::Core() :
		m_log(new Log()),
		m_config(new Config()),
		m_window(new Window()),
		m_gui(new Gui())
	{
		
	}

	Core::~Core()
	{
		AN_DELETE(m_gui);
		AN_DELETE(m_window);
		AN_DELETE(m_config);
		AN_DELETE(m_log);
	}

	bool Core::Initialize()
	{
		AN_CHECK(m_log->Initialize());
		AN_CHECK(m_config->Initialize());
		AN_CHECK(m_window->Initialize());
		AN_CHECK(m_gui->Initialize());

		return true;
	}

}
