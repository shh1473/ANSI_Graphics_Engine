#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace Example
{

	class TextureScene : public ExampleScene
	{
	public:
		explicit TextureScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* === Gui === */
		bool m_isWireframe;

	private: /* === Objects === */
		AN::Object * m_wall{ nullptr };
		AN::Object * m_camera{ nullptr };
		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resources === */
		AN::Shader * m_textureShader{ nullptr };

		AN::Geometry * m_planeGeometry{ nullptr };
		AN::VertexArray * m_wallVA{ nullptr };

		AN::Texture * m_wallTexture{ nullptr };

	};

}
