#pragma once

#include "common/ansi_common_render.h"
#include "object/component/ansi_component.h"
#include "object/component/camera/output_param/ansi_output_param.h"
#include "object/component/camera/raster_param/ansi_raster_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class GBufferOutput;

	class Camera : public Component
	{
	public:
		explicit Camera(Object * object, CameraType type = CameraType::Camera, bool isEnableGBuffers = false);
		virtual ~Camera();

		bool OnUpdate() override;
		bool InitializeGBuffer();
		bool CheckFrustum(const glm::vec3 & worldPosition, float radius);

		void SetIsPerspective(bool isPerspective) { m_isPerspective.Set(isPerspective); }
		void SetFov(float fov) { m_fov.Set(fov); }
		void SetNear(float nearZ) { m_near.Set(nearZ); }
		void SetFar(float farZ) { m_far.Set(farZ); }
		void SetSize(float width, float height) { m_width.Set(width); m_height.Set(height); }
		void AddWidth(float width) { m_width.Set(m_width.Get() + width); }
		void AddHeight(float height) { m_height.Set(m_height.Get() + height); }
		void SetIsEnableFrustumCulling(bool isEnable) { m_isEnableFrustumCulling = isEnable; }

		bool GetIsEnableFrustumCulling() const { return m_isEnableFrustumCulling; }
		const glm::vec3 & GetLookAt() const { return m_lookAt; }
		const glm::mat4 & GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4 & GetProjMatrix() const { return m_projMatrix; }
		const glm::mat4 & GetViewProjMatrix() const { return m_viewProjMatrix; }
		float GetNear() const { return m_near.Get(); }
		float GetFar() const { return m_far.Get(); }
		RasterParam * Raster() const { return m_rasterParam; }
		OutputParam * Output() const { return m_outputParam; }
		GBufferOutput * GetGBufferOutput() const { return m_gBufferOutput; }

	private:
		void UpdateViewMatrix();
		void UpdateProjMatrix();

		static const bool m_DefaultIsPerspective;
		static const float m_DefaultFov;
		static const float m_DefaultNear;
		static const float m_DefaultFar;
		static const float m_DefaultWidth;
		static const float m_DefaultHeight;

		bool m_isEnableFrustumCulling;
		CameraType m_type;
		glm::vec3 m_lookAt;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projMatrix;
		glm::mat4 m_viewProjMatrix;
		StateChecker<bool> m_isPerspective;
		StateChecker<float> m_fov;
		StateChecker<float> m_near;
		StateChecker<float> m_far;
		StateChecker<float> m_width;
		StateChecker<float> m_height;
		RasterParam * m_rasterParam;
		OutputParam * m_outputParam;
		GBufferOutput * m_gBufferOutput;

	};

}
