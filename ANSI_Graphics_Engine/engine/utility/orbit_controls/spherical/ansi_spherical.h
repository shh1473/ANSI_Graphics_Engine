#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class Spherical
	{
	public:
		explicit Spherical(float radius = 1.0f, float phi = 0.0f, float theta = 0.0f);

		void MakeSafe();

		void SetFromCartesianCoords(const glm::vec3 & coords);
		void Set(float radius, float phi, float theta) { m_radius = radius; m_phi = phi; m_theta = theta; }
		void SetRadius(float radius) { m_radius = radius; }
		void SetPhi(float phi) { m_phi = phi; }
		void SetTheta(float theta) { m_theta = theta; }
		void Add(float radius, float phi, float theta) { m_radius += radius; m_phi += phi; m_theta += theta; }
		void AddRadius(float radius) { m_radius += radius; }
		void AddPhi(float phi) { m_phi += phi; }
		void AddTheta(float theta) { m_theta += theta; }

		static float GetEpsilon() { return m_Epsilon; }
		glm::vec3 GetFromSphericalCoords() const;
		float GetRadius() const { return m_radius; }
		float GetPhi() const { return m_phi; }
		float GetTheta() const { return m_theta; }

	private:
		static float m_Epsilon;

		float m_radius;
		float m_phi;
		float m_theta;

	};

}
