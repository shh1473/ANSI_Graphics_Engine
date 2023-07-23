#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace Example
{

	class CapsuleLightsScene : public ExampleScene
	{
	public:
		explicit CapsuleLightsScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private:
		void UpdateLightDistance(float distance);

	private: /* === Constants === */
		static constexpr unsigned m_CapsuleLightCount{ 3 };
		static const float m_DefaultSpecularIntensity;
		static const float m_DefaultSpecularPower;
		static const float m_DefaultLightRadius;
		static const float m_DefaultLightLength;
		static const float m_DefaultLightDistance;
		static const glm::vec3 m_DefaultLightDirection;
		static const glm::vec3 m_DefaultLightColors[m_CapsuleLightCount];

	private: /* === Gui === */
		bool m_isWireframe;
		float m_specularIntensity;
		float m_specularPower;
		float m_lightRadius;
		float m_lightLength;
		float m_lightRotation;
		float m_lightDistance;
		glm::vec3 m_lightHeights;

	private: /* === Objects === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_plane{ nullptr };
		AN::Object * m_lightGroup{ nullptr };
		AN::Object * m_capsuleLights[m_CapsuleLightCount]{ nullptr, };
		AN::Object * m_camera{ nullptr };
		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resources === */
		AN::Shader * m_capsuleLights3Shader{ nullptr };

		AN::Geometry * m_rgratGeometry{ nullptr };
		AN::VertexArray * m_rgratVA{ nullptr };

		AN::Geometry * m_planeGeometry{ nullptr };
		AN::VertexArray * m_planeVA{ nullptr };

	};

}
