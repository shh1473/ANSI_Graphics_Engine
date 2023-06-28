#include "ansi_spherical.h"

namespace AN
{

	float Spherical::m_Epsilon{ 0.000001f };

	Spherical::Spherical(float radius, float phi, float theta) :
		m_radius(radius),
		m_phi(phi),
		m_theta(theta)
	{

	}

	void Spherical::MakeSafe()
	{
		m_phi = glm::clamp(m_phi, m_Epsilon, PI - m_Epsilon);
	}

	void Spherical::SetFromCartesianCoords(const glm::vec3 & coords)
	{
		m_radius = std::sqrt(coords.x * coords.x + coords.y * coords.y + coords.z * coords.z);

		if (m_radius == 0)
		{
			m_theta = 0;
			m_phi = 0;
		}
		else
		{
			m_theta = std::atan2(coords.x, coords.z);
			m_phi = std::acos(glm::clamp(coords.y / m_radius, -1.0f, 1.0f));
		}
	}

	glm::vec3 Spherical::GetFromSphericalCoords() const
	{
		const float sinPhiRadius = std::sin(m_phi) * m_radius;
		return glm::vec3(sinPhiRadius * std::sin(m_theta), std::cos(m_phi) * m_radius, sinPhiRadius * std::cos(m_theta));
	}

}
