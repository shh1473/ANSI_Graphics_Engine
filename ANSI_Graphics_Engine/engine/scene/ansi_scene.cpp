#include "scene/ansi_scene.h"

#include "scene/render_executor/ansi_render_executor.h"
#include "scene/resource_storage/ansi_resource_storage.h"
#include "object/ansi_object.h"

namespace AN
{

	Scene::Scene(const std::string & name) :
		m_name(name),
		m_renderExecutor(new RenderExecutor()),
		m_resourceStorage(new ResourceStorage()),
		m_objects()
	{

	}

	Scene::~Scene()
	{
		for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
		{
			AN_DELETE(iter->second);
		}
	}

	bool Scene::Initialize()
	{
		return true;
	}

	bool Scene::OnEnter()
	{
		return true;
	}

	bool Scene::OnExit()
	{
		return true;
	}

	bool Scene::OnFixedUpdate()
	{
		return true;
	}

	bool Scene::OnUpdate()
	{
		return true;
	}

	bool Scene::OnLateUpdate()
	{
		return true;
	}

	bool Scene::OnRender()
	{
		return /*m_renderExecutor.OnRender();*/true;
	}

	bool Scene::OnDefaultUpdate()
	{
		for (const auto & iter : m_objects)
		{
			AN_CHECK(iter.second->OnUpdate());
			AN_CHECK(iter.second->OnDefaultUpdate());
		}

		return true;
	}

	bool Scene::OnDefaultFixedUpdate()
	{
		for (const auto & iter : m_objects)
		{
			AN_CHECK(iter.second->OnFixedUpdate());
			AN_CHECK(iter.second->OnDefaultFixedUpdate());
		}

		return true;
	}

	bool Scene::OnDefaultLateUpdate()
	{
		for (auto iter = m_objects.begin(); iter != m_objects.end();)
		{
			if (iter->second->GetIsDeleted())
			{
				AN_DELETE(iter->second);
				m_objects.erase(iter);
			}
			else { ++iter; }
		}

		for (const auto & iter : m_objects)
		{
			AN_CHECK(iter.second->OnLateUpdate());
			AN_CHECK(iter.second->OnDefaultLateUpdate());
		}

		return true;
	}

}