#include "ansi_transform.h"

#include "object/ansi_object.h"

namespace AN
{

	Transform::Transform(Object * object) :
		Component(object),
		m_isChangedTransform(false),
		m_isChangedMatrix(false),
		m_worldPosition(0.0f),
		m_worldMatrix(1.0f),
		m_position(0.0f),
		m_rotation(0.0f),
		m_scale(1.0f),
		m_parentMatrix(1.0f)
	{

	}

	bool Transform::OnLateUpdate()
	{
		if (m_position.Check() || m_rotation.Check() || m_scale.Check())
		{
			m_isChangedTransform = true;
			m_worldMatrix = glm::translate(glm::mat4(1.0f), m_position.Get());
			m_worldMatrix *= glm::mat4_cast(ConvertXYZToQuat());
			m_worldMatrix *= glm::scale(glm::mat4(1.0f), m_scale.Get());
			m_position.Reset();
			m_rotation.Reset();
			m_scale.Reset();
		}

		if (m_isChangedTransform || (GetObject()->GetParent() && m_parentMatrix.Check()))
		{
			m_isChangedTransform = false;
			m_isChangedMatrix = true;

			if (GetObject()->GetParent())
			{
				m_worldMatrix *= m_parentMatrix.Get();
			}

			for (const auto & iter : GetObject()->GetChildren())
			{
				iter.second->GetTransform()->m_parentMatrix.Set(m_worldMatrix);
			}

			m_worldPosition = glm::vec3(m_worldMatrix[3]);
			m_parentMatrix.Reset();
		}
		else
		{
			m_isChangedMatrix = false;
		}

		return true;
	}

	void Transform::Reset()
	{
		m_worldMatrix = glm::mat4(1.0f);
		m_position.Set(glm::vec3(0.0f));
		m_rotation.Set(glm::vec3(0.0f));
		m_scale.Set(glm::vec3(1.0f));
		m_parentMatrix.Set(glm::mat4(1.0f));

		m_position.Reset();
		m_rotation.Reset();
		m_scale.Reset();
		m_parentMatrix.Reset();
	}

	glm::quat Transform::ConvertXYZToQuat() const
	{
		static glm::vec3 radianRotation(0.0f);

		radianRotation = glm::radians(m_rotation.Get());
		const float c1 = cosf(radianRotation.x * 0.5f);
		const float c2 = cosf(radianRotation.y * 0.5f);
		const float c3 = cosf(radianRotation.z * 0.5f);
		const float s1 = sinf(radianRotation.x * 0.5f);
		const float s2 = sinf(radianRotation.y * 0.5f);
		const float s3 = sinf(radianRotation.z * 0.5f);

		return glm::quat(
			c1 * c2 * c3 - s1 * s2 * s3,
			s1 * c2 * c3 + c1 * s2 * s3,
			c1 * s2 * c3 - s1 * c2 * s3,
			c1 * c2 * s3 + s1 * s2 * c3);
	}

}