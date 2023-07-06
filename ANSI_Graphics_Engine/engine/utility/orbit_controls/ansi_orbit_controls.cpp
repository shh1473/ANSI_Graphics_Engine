// >========================================================================================<
//  본 ansi_orbit_controls.cpp 파일의 코드는 Three.js의 OrbitControls.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 마우스로만 조작하는 것을 전제로 하여
//  터치 패드와 키보드 조작 기능은 제거했으니 전체 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/examples/jsm/controls/OrbitControls.js
// >========================================================================================<

#include "ansi_orbit_controls.h"

#include "core/window/ansi_window.h"
#include "core/gui/ansi_gui.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"
#include "object/component/camera/ansi_camera.h"

namespace AN
{

	OrbitControls::OrbitControls(Camera * camera, float panSpeed, float rotateSpeed, float zoomSpeed) :
		m_isEnabled(true),
		m_dollyScale(1.0f),
		m_zoomSpeed(zoomSpeed),
		m_rotateSpeed(rotateSpeed),
		m_panSpeed(panSpeed),
		m_minDistance(0.0f),
		m_maxDistance(std::numeric_limits<float>::infinity()),
		m_minZoom(0.0f),
		m_maxZoom(std::numeric_limits<float>::infinity()),
		m_minPolarAngle(PI * 0.1f),
		m_maxPolarAngle(PI * 0.9f),
		m_minAzimuthAngle(-std::numeric_limits<float>::infinity()),
		m_maxAzimuthAngle(std::numeric_limits<float>::infinity()),
		m_state(State::None),
		m_spherical(),
		m_sphericalDelta(),
		m_panOffset(0.0f),
		m_panStart(0.0f),
		m_panEnd(0.0f),
		m_panDelta(0.0f),
		m_rotateStart(0.0f),
		m_rotateEnd(0.0f),
		m_rotateDelta(0.0f),
		m_dollyStart(0.0f),
		m_dollyEnd(0.0f),
		m_dollyDelta(0.0f),
		m_target(0.0f),
		m_resetPosition(camera->GetObject()->GetTransform()->GetPosition()),
		m_camera(camera),
		m_object(camera->GetObject())
	{

	}

	void OrbitControls::OnMouseDown(int button, const glm::vec2 & position)
	{
		if (!m_isEnabled || m_state != State::None || Core::GetGui()->GetIsWindowHovered()) { return; }
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
			{
				m_rotateStart.x = position.x;
				m_rotateStart.y = position.y;
				m_state = State::Rotate;
			} break;
			case GLFW_MOUSE_BUTTON_RIGHT:
			{
				m_panStart.x = position.x;
				m_panStart.y = position.y;
				m_state = State::Pan;
			} break;
		}
	}

	void OrbitControls::OnMouseUp(int button)
	{
		if (!m_isEnabled || m_state == State::None) { return; }
		switch (m_state)
		{
			case State::Rotate: { if (button == GLFW_MOUSE_BUTTON_LEFT) { m_state = State::None; } } break;
			case State::Pan: { if (button == GLFW_MOUSE_BUTTON_RIGHT) { m_state = State::None; } } break;
		}
	}

	void OrbitControls::OnMouseMove(const glm::vec2 & position)
	{
		if (!m_isEnabled) { return; }
		switch (m_state)
		{
			case State::Rotate: { HandleMouseMoveRotate(position); } break;
			case State::Pan: { HandleMouseMovePan(position); } break;
		}
	}

	void OrbitControls::OnMouseWheel(float deltaY)
	{
		if (!m_isEnabled) { return; }
		HandleMouseWheel(deltaY);
	}

	void OrbitControls::Reset()
	{
		m_target = glm::vec3(0.0f);
		m_object->GetTransform()->SetPosition(m_resetPosition);
		m_camera->SetLookAt(m_target);
		m_spherical.SetFromCartesianCoords(m_object->GetTransform()->GetPosition() - m_target);
		m_spherical.SetRadius(GetDistance());
		m_spherical.SetRadius(glm::clamp(m_spherical.GetRadius(), m_minDistance, m_maxDistance));
	}

	float OrbitControls::GetDistance() const
	{
		return glm::length(m_target - m_object->GetTransform()->GetPosition());
	}

	void OrbitControls::Update()
	{
		m_spherical.SetFromCartesianCoords(m_object->GetTransform()->GetPosition() - m_target);
		m_spherical.AddTheta(m_sphericalDelta.GetTheta());
		m_spherical.AddPhi(m_sphericalDelta.GetPhi());

		if (std::isfinite(m_minAzimuthAngle) && std::isfinite(m_maxAzimuthAngle))
		{

			if (m_minAzimuthAngle < -PI) m_minAzimuthAngle += PI2; else if (m_minAzimuthAngle > PI) m_minAzimuthAngle -= PI2;
			if (m_maxAzimuthAngle < -PI) m_maxAzimuthAngle += PI2; else if (m_maxAzimuthAngle > PI) m_maxAzimuthAngle -= PI2;
			if (m_minAzimuthAngle <= m_maxAzimuthAngle)
			{
				m_spherical.SetTheta(glm::clamp(m_spherical.GetTheta(), m_minAzimuthAngle, m_maxAzimuthAngle));
			}
			else
			{
				m_spherical.SetTheta((m_spherical.GetTheta() > (m_minAzimuthAngle + m_maxAzimuthAngle) * 0.5f) ?
					std::max(m_minAzimuthAngle, m_spherical.GetTheta()) :
					std::min(m_maxAzimuthAngle, m_spherical.GetTheta()));
			}

		}

		m_spherical.SetPhi(glm::clamp(m_spherical.GetPhi(), m_minPolarAngle, m_maxPolarAngle));
		m_spherical.MakeSafe();
		m_spherical.SetRadius(m_spherical.GetRadius() * m_dollyScale);
		m_spherical.SetRadius(glm::clamp(m_spherical.GetRadius(), m_minDistance, m_maxDistance));
		
		m_target += m_panOffset;
		m_object->GetTransform()->SetPosition(m_target + m_spherical.GetFromSphericalCoords());
		m_object->GetTransform()->SetRotationY(glm::degrees(m_spherical.GetTheta()));
		m_camera->SetLookAt(m_target);

		m_sphericalDelta.Set(0.0f, 0.0f, 0.0f);
		m_panOffset = glm::vec3(0.0f);
		m_dollyScale = 1.0f;
	}

	void OrbitControls::HandleMouseMoveRotate(const glm::vec2 & position)
	{
		m_rotateEnd = position;
		m_rotateDelta = (m_rotateEnd - m_rotateStart) * m_rotateSpeed;
		m_rotateStart = m_rotateEnd;

		RotateLeft(m_rotateDelta.x / static_cast<float>(Core::GetWindow()->GetClientSize().x) * PI2);
		RotateUp(m_rotateDelta.y / static_cast<float>(Core::GetWindow()->GetClientSize().y) * PI2);
		Update();
	}

	void OrbitControls::HandleMouseMovePan(const glm::vec2 & position)
	{
		m_panEnd = position;
		m_panDelta = (m_panEnd - m_panStart) * m_panSpeed;
		m_panStart = m_panEnd;

		Pan(m_panDelta);
		Update();
	}

	void OrbitControls::HandleMouseWheel(float deltaY)
	{
		if (deltaY > 0) { DollyIn(std::pow(0.95f, m_zoomSpeed)); }
		else { DollyOut(std::pow(0.95f, m_zoomSpeed)); }
		Update();
	}

	void OrbitControls::Pan(const glm::vec2 & panDelta)
	{
		if (m_camera->GetIsPerspective())
		{
			float targetDistance = glm::length(m_object->GetTransform()->GetPosition() - m_target) * std::tan(glm::radians(m_camera->GetFov() * 0.5f)) * 2.0f;

			PanLeft(targetDistance * panDelta.x / Core::GetWindow()->GetClientSize().y, m_object->GetTransform()->GetWorldMatrix());
			PanUp(targetDistance * panDelta.y / Core::GetWindow()->GetClientSize().y, m_object->GetTransform()->GetWorldMatrix());
		}
		else
		{
			PanLeft(panDelta.x * m_camera->GetWidth() / m_camera->GetZoom() / Core::GetWindow()->GetClientSize().x, m_object->GetTransform()->GetWorldMatrix());
			PanUp(panDelta.y * m_camera->GetHeight() / m_camera->GetZoom() / Core::GetWindow()->GetClientSize().y, m_object->GetTransform()->GetWorldMatrix());
		}
	}

	void OrbitControls::RotateLeft(float angle)
	{
		m_sphericalDelta.AddTheta(-angle);
	}

	void OrbitControls::RotateUp(float angle)
	{
		m_sphericalDelta.AddPhi(-angle);
	}

	void OrbitControls::PanLeft(float distance, const glm::mat4 & objectMatrix)
	{
		static glm::vec3 v(0.0f);
		v = objectMatrix[0];
		v *= -distance;
		m_panOffset += v;
	}

	void OrbitControls::PanUp(float distance, const glm::mat4 & objectMatrix)
	{
		static glm::vec3 v(0.0f);
		v = objectMatrix[1];
		v *= distance;
		m_panOffset += v;
	}

	void OrbitControls::DollyOut(float dollyScale)
	{
		if (m_camera->GetIsPerspective()) { m_dollyScale /= dollyScale; }
		else { m_camera->SetZoom(glm::clamp(m_camera->GetZoom() * dollyScale, m_minZoom, m_maxZoom)); }
	}

	void OrbitControls::DollyIn(float dollyScale)
	{
		if (m_camera->GetIsPerspective()) { m_dollyScale *= dollyScale; }
		else { m_camera->SetZoom(glm::clamp(m_camera->GetZoom() / dollyScale, m_minZoom, m_maxZoom)); }
	}

}
