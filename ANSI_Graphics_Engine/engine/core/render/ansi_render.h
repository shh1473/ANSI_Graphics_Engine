#pragma once

#include "common/ansi_common_render.h"
#include "core/ansi_core.h"

namespace AN
{

	class Camera;
	class Renderer;
	class InputExecutor;
	class RasterExecutor;
	class ShaderExecutor;
	class OutputExecutor;
	class BuiltInResources;

	class Render
	{
	public:
		explicit Render();
		~Render();

		bool Initialize();
		void Reset();

		bool OnRender();

		void AddCamera(Camera * camera, CameraType type) { m_cameras[static_cast<unsigned>(type)].push_back(camera); }
		void AddRenderer(Renderer * renderer, RenderType type) { m_renderers[static_cast<unsigned>(type)].push_back(renderer); }

		void RemoveCamera(Camera * camera, CameraType type)
		{
			unsigned typeIndex{ static_cast<unsigned>(type) };
			m_cameras[typeIndex].erase(std::find(m_cameras[typeIndex].begin(), m_cameras[typeIndex].end(), camera));
		}
		void RemoveRenderer(Renderer * renderer, RenderType type)
		{
			unsigned typeIndex{ static_cast<unsigned>(type) };
			m_renderers[typeIndex].erase(std::find(m_renderers[typeIndex].begin(), m_renderers[typeIndex].end(), renderer));
		}

		Camera * GetCurrentCamera() const { return m_currentCamera; }
		BuiltInResources * GetBuiltInResources() const { return m_builtInResources; }

	private:
		bool Draw();

		Camera * m_currentCamera;
		InputExecutor * m_inputExecutor;
		RasterExecutor * m_rasterExecutor;
		ShaderExecutor * m_shaderExecutor;
		OutputExecutor * m_outputExecutor;
		BuiltInResources * m_builtInResources;
		std::vector<Camera *> m_cameras[CameraTypeCount];
		std::vector<Renderer *> m_renderers[RenderTypeCount];

	};

}