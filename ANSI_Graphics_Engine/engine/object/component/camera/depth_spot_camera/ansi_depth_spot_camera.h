#pragma once

#include "object/component/camera/ansi_camera.h"

namespace AN
{

	class DepthSpotCamera : public Camera
	{
	public:
		explicit DepthSpotCamera(Object * object);
		virtual ~DepthSpotCamera();

		bool CreateDepthMap();

		Texture * GetDepthMap() const { return m_depthMap; }

	private:
		Texture * m_depthMap;

	};

}
