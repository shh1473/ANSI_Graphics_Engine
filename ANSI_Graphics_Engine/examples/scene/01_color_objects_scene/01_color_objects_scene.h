#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ColorShader;

	class ColorObjectsScene : public AN::Scene
	{
	public:
		explicit ColorObjectsScene();
		virtual ~ColorObjectsScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private: /* === Logics === */
		ColorShader * m_boxColorShader{ nullptr };
		ColorShader * m_sphereColorShader{ nullptr };
		ColorShader * m_cylinderColorShader{ nullptr };

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
