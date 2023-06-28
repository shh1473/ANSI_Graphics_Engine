#pragma once

#include "object/component/ansi_component.h"
#include "utility/state_checker/ansi_state_checker_math.h"

namespace AN
{

	class Transform : public Component
	{
	public:
		explicit Transform(Object * object);

		bool OnLateUpdate() override;

		void Reset();

		void SetPosition(const glm::vec3 & position) { m_position.Set(position); }
		void SetPosition(float x, float y, float z) { m_position.Set(x, y, z); }
		void SetPositionX(float x) { m_position.SetX(x); }
		void SetPositionY(float y) { m_position.SetY(y); }
		void SetPositionZ(float z) { m_position.SetZ(z); }
		void SetRotation(const glm::vec3 & rotation) { m_rotation.Set(rotation); }
		void SetRotation(float x, float y, float z) { m_rotation.Set(x, y, z); }
		void SetRotationX(float x) { m_rotation.SetX(x); }
		void SetRotationY(float y) { m_rotation.SetY(y); }
		void SetRotationZ(float z) { m_rotation.SetZ(z); }
		void SetScale(const glm::vec3 & scale) { m_scale.Set(scale); }
		void SetScale(float x, float y, float z) { m_scale.Set(x, y, z); }
		void SetScaleX(float x) { m_scale.SetX(x); }
		void SetScaleY(float y) { m_scale.SetY(y); }
		void SetScaleZ(float z) { m_scale.SetZ(z); }

		void AddPosition(const glm::vec3 & position) { m_position.Add(position); }
		void AddPosition(float x, float y, float z) { m_position.Add(x, y, z); }
		void AddPositionX(float x) { m_position.AddX(x); }
		void AddPositionY(float y) { m_position.AddY(y); }
		void AddPositionZ(float z) { m_position.AddZ(z); }
		void AddRotation(const glm::vec3 & rotation) { m_rotation.Add(rotation); }
		void AddRotation(float x, float y, float z) { m_rotation.Add(x, y, z); }
		void AddRotationX(float x) { m_rotation.AddX(x); }
		void AddRotationY(float y) { m_rotation.AddY(y); }
		void AddRotationZ(float z) { m_rotation.AddZ(z); }
		void AddScale(const glm::vec3 & scale) { m_scale.Add(scale); }
		void AddScale(float x, float y, float z) { m_scale.Add(x, y, z); }
		void AddScaleX(float x) { m_scale.AddX(x); }
		void AddScaleY(float y) { m_scale.AddY(y); }
		void AddScaleZ(float z) { m_scale.AddZ(z); }

		bool GetIsChangedMatrix() const { return m_isChangedMatrix; }
		const glm::vec3 & GetPosition() const { return m_position.Get(); }
		const glm::vec3 & GetRotation() const { return m_rotation.Get(); }
		const glm::vec3 & GetScale() const { return m_scale.Get(); }
		const glm::vec3 & GetWorldPosition() const { return m_worldPosition; }
		const glm::mat4 & GetWorldMatrix() const { return m_worldMatrix; }
		const glm::mat4 & GetParentMatrix() const { return m_parentMatrix.Get(); }

	private:
		glm::quat ConvertXYZToQuat() const;

		bool m_isChangedTransform;
		bool m_isChangedMatrix;
		glm::vec3 m_worldPosition;
		glm::mat4 m_worldMatrix;
		StateCheckerVec3 m_position;
		StateCheckerVec3 m_rotation;
		StateCheckerVec3 m_scale;
		StateCheckerMat4 m_parentMatrix;

	};

}