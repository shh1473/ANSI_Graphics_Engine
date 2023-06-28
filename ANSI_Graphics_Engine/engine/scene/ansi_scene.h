#pragma once

#include "common/ansi_common.h"

namespace AN
{
	class Object;
	class RenderExecutor;
	class ResourceStorage;

	class Scene
	{
	public:
		explicit Scene();
		virtual ~Scene();

		virtual bool Initialize();
		virtual bool OnEnter();
		virtual bool OnExit();
		virtual bool OnUpdate();
		virtual bool OnFixedUpdate();
		virtual bool OnLateUpdate();
		virtual bool OnRenderGui();
		virtual bool CreateResources();

		bool OnDefaultUpdate();
		bool OnDefaultFixedUpdate();
		bool OnDefaultLateUpdate();

		template <typename T>
		T * AddObject(T * object)
		{
			return static_cast<T *>(m_objects[object->GetName()] = object);
		}

		template <typename T>
		T * FindObject(const std::string & name)
		{
			if (m_objects.count(name) == 0) { return nullptr; }
			return static_cast<T *>(m_objects[name]);
		}

		ResourceStorage * GetResources() const { return m_resourceStorage; }
		const std::unordered_map<std::string, Object *> & GetObjects() const { return m_objects; }

	private:
		ResourceStorage * m_resourceStorage;
		std::unordered_map<std::string, Object *> m_objects;

	};

}