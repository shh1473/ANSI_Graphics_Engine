#pragma once

#include "common/ansi_common.h"

namespace AN
{
	class Camera;
	class PackingCamera;
	class DeferredCamera;
	class ForwardCamera;
	class PackingRenderer;
	class DeferredRenderer;
	class ForwardRenderer;
	class ComputeRenderer;

	class RenderExecutor
	{
	public:
		explicit RenderExecutor();

		bool OnRender();

		void AddPackingCamera(PackingCamera * camera) { m_packingCameras.push_back(camera); }
		void AddDeferredCamera(DeferredCamera * camera) { m_deferredCameras.push_back(camera); }
		void AddForwardCamera(ForwardCamera * camera) { m_forwardCameras.push_back(camera); }
		void AddPackingRenderer(PackingRenderer * renderer) { m_packingRenderers.push_back(renderer); }
		void AddDeferredRenderer(DeferredRenderer * renderer) { m_deferredRenderers.push_back(renderer); }
		void AddForwardRenderer(ForwardRenderer * renderer) { m_forwardRenderers.push_back(renderer); }
		void AddComputeRenderer(ComputeRenderer * renderer) { m_computeRenderers.push_back(renderer); }

		void RemovePackingCamera(PackingCamera * camera) { m_packingCameras.erase(std::find(m_packingCameras.begin(), m_packingCameras.end(), camera)); }
		void RemoveDeferredCamera(DeferredCamera * camera) { m_deferredCameras.erase(std::find(m_deferredCameras.begin(), m_deferredCameras.end(), camera)); }
		void RemoveForwardCamera(ForwardCamera * camera) { m_forwardCameras.erase(std::find(m_forwardCameras.begin(), m_forwardCameras.end(), camera)); }
		void RemovePackingRenderer(PackingRenderer * renderer) { m_packingRenderers.erase(std::find(m_packingRenderers.begin(), m_packingRenderers.end(), renderer)); }
		void RemoveDeferredRenderer(DeferredRenderer * renderer) { m_deferredRenderers.erase(std::find(m_deferredRenderers.begin(), m_deferredRenderers.end(), renderer)); }
		void RemoveForwardRenderer(ForwardRenderer * renderer) { m_forwardRenderers.erase(std::find(m_forwardRenderers.begin(), m_forwardRenderers.end(), renderer)); }
		void RemoveComputeRenderer(ComputeRenderer * renderer) { m_computeRenderers.erase(std::find(m_computeRenderers.begin(), m_computeRenderers.end(), renderer)); }

		Camera * GetCurrentCamera() const noexcept { return m_currentCamera; }

	private:
		Camera * m_currentCamera;
		std::vector<PackingCamera *> m_packingCameras;
		std::vector<DeferredCamera *> m_deferredCameras;
		std::vector<ForwardCamera *> m_forwardCameras;
		std::vector<PackingRenderer *> m_packingRenderers;
		std::vector<DeferredRenderer *> m_deferredRenderers;
		std::vector<ForwardRenderer *> m_forwardRenderers;
		std::vector<ComputeRenderer *> m_computeRenderers;

	};

}