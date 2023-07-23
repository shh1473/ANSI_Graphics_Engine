#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace Example
{

	class ColorsScene : public ExampleScene
	{
	public:
		explicit ColorsScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* === Gui === */
		bool m_isWireframe;

	private: /* === Objects === */
		AN::Object * m_box{ nullptr };
		AN::Object * m_sphere{ nullptr };
		AN::Object * m_cylinder{ nullptr };
		AN::Object * m_camera{ nullptr };
		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resources === */
		AN::Shader * m_colorShader{ nullptr };

		AN::Geometry * m_boxGeometry{ nullptr };
		AN::VertexArray * m_boxVA{ nullptr };
		AN::Geometry * m_sphereGeometry{ nullptr };
		AN::VertexArray * m_sphereVA{ nullptr };
		AN::Geometry * m_cylinderGeometry{ nullptr };
		AN::VertexArray * m_cylinderVA{ nullptr };

	};

}
