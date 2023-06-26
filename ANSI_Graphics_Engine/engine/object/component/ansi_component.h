#pragma once

#include "common/ansi_common.h"

namespace AN
{
	class Object;

	class Component
	{
	public:
		explicit Component(Object * object);
		virtual ~Component();

		virtual bool OnUpdate();
		virtual bool OnFixedUpdate();
		virtual bool OnLateUpdate();

		void SetIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }

		bool GetIsEnabled() const { return m_isEnabled; }
		Object * GetObject() const { return m_object; }

	private:
		bool m_isEnabled;
		Object * m_object;

	};

}