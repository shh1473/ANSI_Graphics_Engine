#include "ansi_render_executor.h"

namespace AN
{

	RenderExecutor::RenderExecutor() :
		m_currentCamera(nullptr),
		m_forwardCameras(),
		m_deferredCameras(),
		m_packingCameras(),
		m_forwardRenderers(),
		m_deferredRenderers(),
		m_packingRenderers(),
		m_computeRenderers()
	{

	}

	bool RenderExecutor::OnRender()
	{
		/*for (auto forwardCameraIter : m_forwardCameras)
		{
			m_currentCamera = forwardCameraIter;
			m_currentCamera->Ready();

			for (auto iter : m_forwardRenderers)
			{
				RF_BOOL(iter->Render());
			}
		}

		for (auto packingCameraIter : m_packingCameras)
		{
			m_currentCamera = packingCameraIter;
			m_currentCamera->Ready();

			for (auto iter : m_packingRenderers)
			{
				RF_BOOL(iter->Render());
			}
		}

		for (auto deferredCameraIter : m_deferredCameras)
		{
			m_currentCamera = deferredCameraIter;
			m_currentCamera->Ready();

			for (auto iter : m_deferredRenderers)
			{
				RF_BOOL(iter->Render());
			}
		}

		for (auto iter : m_computeRenderers)
		{
			RF_BOOL(iter->Render());
		}*/

		return true;
	}

}