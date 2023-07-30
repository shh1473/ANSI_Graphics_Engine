#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{

	class CapsuleLightsScene : public ExampleScene
	{
	public:
		explicit CapsuleLightsScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private:
		void UpdateLightDistance(float distance);

	private: /* === Gui === */
		float m_specularIntensity;
		float m_specularPower;
		float m_lightRadius;
		float m_lightLength;
		float m_lightRotation;
		float m_lightDistance;
		glm::vec3 m_lightHeights;

	private: /* === Object === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_plane{ nullptr };
		AN::Object * m_lightGroup{ nullptr };
		AN::Object * m_capsuleLights[3]{ nullptr, };
		AN::Object * m_camera{ nullptr };

		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resource === */
		AN::Shader * m_capsuleLights3Shader{ nullptr };

		AN::VertexArray * m_rgratVA{ nullptr };
		AN::VertexArray * m_planeVA{ nullptr };

	};

}
