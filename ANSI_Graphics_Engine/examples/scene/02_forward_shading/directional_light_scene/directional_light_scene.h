#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{

	class DirectionalLightScene : public ExampleScene
	{
	public:
		explicit DirectionalLightScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* === Gui === */
		float m_specularIntensity;
		float m_specularPower;
		glm::vec3 m_lightColor;
		glm::vec2 m_lightRotation;

	private: /* === Object === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_plane{ nullptr };
		AN::Object * m_directionalLight{ nullptr };
		AN::Object * m_camera{ nullptr };

		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resource === */
		AN::Shader * m_directionalLightShader{ nullptr };

		AN::VertexArray * m_rgratVA{ nullptr };
		AN::VertexArray * m_planeVA{ nullptr };

	};

}
