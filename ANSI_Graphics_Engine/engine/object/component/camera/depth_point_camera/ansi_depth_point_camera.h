#pragma once

#include "object/component/camera/ansi_camera.h"

namespace AN
{

	class DepthPointCamera : public Camera
	{
	public:
		explicit DepthPointCamera(Object * object);
		virtual ~DepthPointCamera();

		bool OnUpdate() override;

		bool CreateDepthMap();

		Texture * GetDepthMap() const { return m_depthMap; }
		float * GetViewProjMatricesAddress() { return &m_viewProjMatrices[0][0][0]; }

	private:
		Texture * m_depthMap;
		glm::mat4 m_viewProjMatrices[6];

	};

}
