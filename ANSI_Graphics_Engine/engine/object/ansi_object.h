#pragma once

#include "common/ansi_common.h"
#include "object/component/transform/ansi_transform.h"

namespace AN
{

	class Object
	{
	public:
		explicit Object(const std::string & name);
		virtual ~Object();

		virtual bool OnFixedUpdate();
		virtual bool OnUpdate();
		virtual bool OnLateUpdate();

		bool OnDefaultUpdate();
		bool OnDefaultFixedUpdate();
		bool OnDefaultLateUpdate();

		void SetIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }
		void SetIsDeleted(bool isDeleted) { m_isDeleted = isDeleted; }

		bool GetIsEnabled() const { return m_isEnabled; }
		bool GetIsDeleted() const { return m_isDeleted; }
		const std::string & GetName() const { return m_name; }
		const std::unordered_map<std::string, Object *> & GetChildren() const { return m_children; }
		const std::unordered_map<std::type_index, Component *> & GetComponents() const { return m_components; }
		Object * GetParent() const { return m_parent; }
		Transform * GetTransform() const { return m_transform; }

	public:
		template <typename T>
		T * AddComponent()
		{
			return static_cast<T *>(m_components[typeid(T)] = new T(this));
		}

		template <typename T>
		T * FindComponent()
		{
			if (m_components.count(typeid(T)) == 0) { return nullptr; }
			return static_cast<T *>(m_components[typeid(T)]);
		}

		template <typename T>
		T * AddChild(T * object)
		{
			object->m_parent = this;
			return static_cast<T *>(m_children[object->GetName()] = object);
		}

		template <typename T>
		T * FindChild(const std::string & name)
		{
			if (m_children.count(name) == 0) { return nullptr; }
			return static_cast<T *>(m_children[name]);
		}

	private:
		bool m_isEnabled;
		bool m_isDeleted;
		std::string m_name;
		std::unordered_map<std::string, Object *> m_children;
		std::unordered_map<std::type_index, Component *> m_components;
		Object * m_parent;
		Transform * m_transform;

	};

}
