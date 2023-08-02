#include "ansi_object.h"

#include "object/component/transform/ansi_transform.h"

namespace AN
{

	Object::Object(const std::string & name) :
		m_isEnabled(true),
		m_isDeleted(false),
		m_isCastShadow(true),
		m_isReceiveShadow(true),
		m_name(name),
		m_children(),
		m_components(),
		m_parent(nullptr),
		m_transform(AddComponent<Transform>())
	{

	}

	Object::~Object()
	{
		for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
		{
			AN_DELETE(iter->second);
		}

		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
		{
			AN_DELETE(iter->second);
		}
	}

	bool Object::OnFixedUpdate()
	{
		return true;
	}

	bool Object::OnUpdate()
	{
		return true;
	}

	bool Object::OnLateUpdate()
	{
		return true;
	}

	bool Object::OnDefaultUpdate()
	{
		for (const auto & iter : m_components)
		{
			if (iter.second->GetIsEnabled()) 
			{
				AN_CHECK(iter.second->OnUpdate());
			}
		}

		for (const auto & iter : m_children)
		{
			if (iter.second->GetIsEnabled())
			{
				AN_CHECK(iter.second->OnUpdate());
				AN_CHECK(iter.second->OnDefaultUpdate());
			}
		}

		return true;
	}

	bool Object::OnDefaultFixedUpdate()
	{
		for (const auto & iter : m_components)
		{
			if (iter.second->GetIsEnabled())
			{
				AN_CHECK(iter.second->OnFixedUpdate());
			}
		}

		for (const auto & iter : m_children)
		{
			if (iter.second->GetIsEnabled())
			{
				AN_CHECK(iter.second->OnFixedUpdate());
				AN_CHECK(iter.second->OnDefaultFixedUpdate());
			}
		}

		return true;
	}

	bool Object::OnDefaultLateUpdate()
	{
		for (auto iter = m_children.begin(); iter != m_children.end();)
		{
			if (iter->second->GetIsDeleted())
			{
				AN_DELETE(iter->second);
				iter = m_children.erase(iter);
			}
			else { ++iter; }
		}

		for (const auto & iter : m_components)
		{
			if (iter.second->GetIsEnabled())
			{
				AN_CHECK(iter.second->OnLateUpdate());
			}
		}

		for (const auto & iter : m_children)
		{
			if (iter.second->GetIsEnabled())
			{
				AN_CHECK(iter.second->OnLateUpdate());
				AN_CHECK(iter.second->OnDefaultLateUpdate());
			}
		}

		return true;
	}

}