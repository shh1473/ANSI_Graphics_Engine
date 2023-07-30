#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{

	class ColorScene : public ExampleScene
	{
	public:
		explicit ColorScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* === Gui === */
		bool m_isWireframe;

	private: /* === Object === */
		AN::Object * m_box{ nullptr };
		AN::Object * m_sphere{ nullptr };
		AN::Object * m_cylinder{ nullptr };
		AN::Object * m_camera{ nullptr };

		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resource === */
		AN::Shader * m_colorShader{ nullptr };

		AN::VertexArray * m_boxVA{ nullptr };
		AN::VertexArray * m_sphereVA{ nullptr };
		AN::VertexArray * m_cylinderVA{ nullptr };

	};

}
