#pragma once

#include "utility/orbit_controls/spherical/ansi_spherical.h"
#include "utility/event_listener/ansi_event_listener.h"

namespace AN
{

	class Camera;
	class Object;

	class OrbitControls : public EventListener
	{
	public:
		explicit OrbitControls(Camera * camera);
		~OrbitControls();

		glm::quat MakeQuatFromUnitVectors(const glm::vec3 & from, const glm::vec3 & to) const
		{
			glm::quat result(1.0f, 0.0f, 0.0f, 0.0f);
			const float r{ glm::dot(from, to) };

			if (r < Spherical::GetEpsilon() - 1.0f)
			{
				result.w = 0.0f;
				if (std::abs(from.x) > std::abs(from.z))
				{
					result.x = -from.y;
					result.y = from.x;
					result.z = 0.0f;
				}
				else
				{
					result.x = 0.0f;
					result.y = -from.z;
					result.z = from.y;
				}
			}
			else
			{
				result.x = from.y * to.z - from.z * to.y;
				result.y = from.z * to.x - from.x * to.z;
				result.z = from.x * to.y - from.y * to.x;
				result.w = r;
			}

			return glm::normalize(result);
		}

		void OnMouseDown(int button, const glm::vec2 & position) override;
		void OnMouseUp(int button) override;
		void OnMouseMove(const glm::vec2 & position) override;
		void OnMouseWheel(float deltaY) override;

		float GetPolarAngle() const { return m_spherical.GetPhi(); };
		float GetAzimuthalAngle() const { return m_spherical.GetTheta(); };
		float GetDistance() const;

	private:
		enum class State { None, Rotate, Pan, Dolly };

		void Update();
		void HandleMouseMoveRotate(const glm::vec2 & position);
		void HandleMouseMovePan(const glm::vec2 & position);
		void HandleMouseWheel(float deltaY);
		void Pan(const glm::vec2 & panDelta);
		void RotateLeft(float angle);
		void RotateUp(float angle);
		void PanLeft(float distance, const glm::mat4 & objectMatrix);
		void PanUp(float distance, const glm::mat4 & objectMatrix);
		void DollyOut(float dollyScale);
		void DollyIn(float dollyScale);

		bool m_isEnabled;
		float m_scale;
		float m_zoomSpeed;
		float m_rotateSpeed;
		float m_panSpeed;
		float m_minDistance;
		float m_maxDistance;
		float m_minZoom;
		float m_maxZoom;
		float m_minPolarAngle;
		float m_maxPolarAngle;
		float m_minAzimuthAngle;
		float m_maxAzimuthAngle;
		State m_state;
		Spherical m_spherical;
		Spherical m_sphericalDelta;
		glm::vec3 m_panOffset;
		glm::vec2 m_panStart;
		glm::vec2 m_panEnd;
		glm::vec2 m_panDelta;
		glm::vec2 m_rotateStart;
		glm::vec2 m_rotateEnd;
		glm::vec2 m_rotateDelta;
		glm::vec2 m_dollyStart;
		glm::vec2 m_dollyEnd;
		glm::vec2 m_dollyDelta;
		glm::vec3 m_target;
		Camera * m_camera;
		Object * m_object;

	};

}
