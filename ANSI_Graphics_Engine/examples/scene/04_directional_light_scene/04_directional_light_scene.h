#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class DirectionalLightShader;

	class DirectionalLightScene : public AN::Scene
	{
	public:
		explicit DirectionalLightScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private:
		static const float m_DefaultSpecularIntensity;
		static const float m_DefaultSpecularPower;
		static const glm::vec3 m_DefaultDirectionalLightColor;
		static const glm::vec3 m_DefaultDirectionalLightDirection;

	private: /* === Gui === */
		bool m_isWireframe;
		float m_specularIntensity;
		float m_specularPower;
		glm::vec3 m_directionalLightColor;
		glm::vec3 m_directionalLightDirection;

	private: /* === Objects === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_directionalLight{ nullptr };
		AN::Object * m_camera{ nullptr };
		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resources === */
		AN::Shader * m_directionalLightShader{ nullptr };

		AN::Geometry * m_rgratGeometry{ nullptr };
		AN::VertexArray * m_rgratVA{ nullptr };

	};

}
