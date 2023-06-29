// >========================================================================================<
//  본 ansi_orbit_controls.h 파일의 코드는 Three.js의 OrbitControls.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 마우스로만 조작하는 것을 전제로 하여
//  터치 패드와 키보드 조작 기능은 제거했으니 전체 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/examples/jsm/controls/OrbitControls.js
// >========================================================================================<

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
		explicit OrbitControls(Camera * camera, float panSpeed = 50.0f, float rotateSpeed = 1.0f, float zoomSpeed = 1.0f);

		void OnMouseDown(int button, const glm::vec2 & position) override;
		void OnMouseUp(int button) override;
		void OnMouseMove(const glm::vec2 & position) override;
		void OnMouseWheel(float deltaY) override;

		void Reset();

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

		float GetDistance() const;

		bool m_isEnabled;
		float m_dollyScale;
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
		glm::vec3 m_resetPosition;
		Camera * m_camera;
		Object * m_object;

	};

}
