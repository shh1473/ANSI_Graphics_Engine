#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{

	class TextureScene : public ExampleScene
	{
	public:
		explicit TextureScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* === Object === */
		AN::Object * m_wall{ nullptr };
		AN::Object * m_camera{ nullptr };

		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resource === */
		AN::Shader * m_textureShader{ nullptr };

		AN::VertexArray * m_wallVA{ nullptr };

		AN::Texture * m_wallTexture{ nullptr };

	};

}
