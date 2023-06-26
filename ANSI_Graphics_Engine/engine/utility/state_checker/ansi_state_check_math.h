#pragma once

#include "common/ansi_common.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class StateCheckerVec3 : public StateChecker<glm::vec3>
	{
	public:
		explicit StateCheckerVec3(float scalar) { m_curValue = m_oldValue = glm::vec3(scalar); }

		void Set(const glm::vec3 & vec3) { m_curValue = vec3; }
		void Set(float x, float y, float z) { m_curValue.x = x; m_curValue.y = y; m_curValue.z = z; }
		void SetX(float x) { m_curValue.x = x; }
		void SetY(float y) { m_curValue.y = y; }
		void SetZ(float z) { m_curValue.z = z; }

		void Add(const glm::vec3 & vec3) { m_curValue += vec3; }
		void Add(float x, float y, float z) { m_curValue.x += x; m_curValue.y += y; m_curValue.z += z; }
		void AddX(float x) { m_curValue.x += x; }
		void AddY(float y) { m_curValue.y += y; }
		void AddZ(float z) { m_curValue.z += z; }

	};

	class StateCheckerMat4 : public StateChecker<glm::mat4>
	{
	public:
		explicit StateCheckerMat4(float scalar) { m_curValue = m_oldValue = glm::mat4(scalar); }

		void Multiply(const glm::mat4 & matrix4x4) { m_curValue *= matrix4x4; }

	};

}
