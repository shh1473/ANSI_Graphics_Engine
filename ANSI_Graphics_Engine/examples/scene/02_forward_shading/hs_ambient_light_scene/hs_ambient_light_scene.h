#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{

	class HSAmbientLightScene : public ExampleScene
	{
	public:
		explicit HSAmbientLightScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* === Gui === */
		glm::vec3 m_ambientLightUpColor;
		glm::vec3 m_ambientLightDownColor;

	private: /* === Object === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_ambientLight{ nullptr };
		AN::Object * m_camera{ nullptr };

		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resource === */
		AN::Shader * m_hsAmbientLightShader{ nullptr };

		AN::VertexArray * m_rgratVA{ nullptr };

	};

}
