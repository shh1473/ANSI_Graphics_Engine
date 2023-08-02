#include "ansi_transform.h"

#include "object/ansi_object.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	Transform::Transform(Object * object) :
		Component(object),
		m_isChangedTransform(false),
		m_isChangedMatrix(false),
		m_eulerOrder(EulerOrder::XYZ),
		m_worldPosition(0.0f),
		m_localMatrix(1.0f),
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

			m_localMatrix = glm::translate(glm::mat4(1.0f), m_position.Get());
			m_localMatrix *= glm::mat4_cast(Converter::EulerToQuat(m_rotation.Get(), m_eulerOrder));
			m_localMatrix *= glm::scale(glm::mat4(1.0f), m_scale.Get());

			m_position.Reset();
			m_rotation.Reset();
			m_scale.Reset();
		}

		if (m_isChangedTransform || (GetObject()->GetParent() && m_parentMatrix.Check()))
		{
			m_isChangedTransform = false;
			m_isChangedMatrix = true;

			m_worldMatrix = m_localMatrix;

			if (GetObject()->GetParent())
			{
				m_worldMatrix = m_parentMatrix.Get() * m_worldMatrix;
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

	glm::vec3 Transform::GetLookAt(const glm::vec3 & direction) const
	{
		return glm::normalize(glm::mat3(m_worldMatrix) * direction);
	}

}