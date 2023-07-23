#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace Example
{

	class DirectionalLightScene : public ExampleScene
	{
	public:
		explicit DirectionalLightScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* === Constants === */
		static const float m_DefaultSpecularIntensity;
		static const float m_DefaultSpecularPower;
		static const glm::vec3 m_DefaultLightColor;
		static const glm::vec2 m_DefaultLightRotation;

	private: /* === Gui === */
		bool m_isWireframe;
		float m_specularIntensity;
		float m_specularPower;
		glm::vec3 m_lightColor;
		glm::vec2 m_lightRotation;

	private: /* === Objects === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_plane{ nullptr };
		AN::Object * m_directionalLight{ nullptr };
		AN::Object * m_camera{ nullptr };
		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resources === */
		AN::Shader * m_directionalLightShader{ nullptr };

		AN::Geometry * m_rgratGeometry{ nullptr };
		AN::VertexArray * m_rgratVA{ nullptr };

		AN::Geometry * m_planeGeometry{ nullptr };
		AN::VertexArray * m_planeVA{ nullptr };

	};

}
