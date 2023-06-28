#include "ansi_core.h"

#include "core/log/ansi_log.h"
#include "core/timer/ansi_timer.h"
#include "core/xml/config/ansi_config.h"
#include "core/window/ansi_window.h"
#include "core/render/ansi_render.h"
#include "core/gui/ansi_gui.h"
#include "core/render/built_in_resources/ansi_built_in_resources.h"

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
		m_timer(new Timer()),
		m_config(new Config()),
		m_window(new Window()),
		m_render(new Render()),
		m_gui(new Gui())
	{
		
	}

	Core::~Core()
	{
		delete m_render->GetBuiltInResources();
		AN_DELETE(m_gui);
		AN_DELETE(m_window);
		AN_DELETE(m_render);
		AN_DELETE(m_config);
		AN_DELETE(m_timer);
		AN_DELETE(m_log);
	}

	bool Core::Initialize()
	{
		AN_CHECK(m_log->Initialize());
		AN_CHECK(m_config->Initialize());
		AN_CHECK(m_window->Initialize(m_config->GetClientWidth(), m_config->GetClientHeight()));
		AN_CHECK(m_render->Initialize());
		AN_CHECK(m_gui->Initialize());

		return true;
	}

}
