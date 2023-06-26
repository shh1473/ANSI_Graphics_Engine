#include "ansi_component.h"

#include "object/ansi_object.h"

namespace AN
{

	Component::Component(Object * object) :
		m_isEnabled(true),
		m_object(object)
	{

	}

	Component::~Component()
	{

	}

	bool Component::OnUpdate()
	{
		return true;
	}

	bool Component::OnFixedUpdate()
	{
		return true;
	}

	bool Component::OnLateUpdate()
	{
		return true;
	}

}