#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ColorCubeScene : public AN::Scene
	{
	public:
		explicit ColorCubeScene();
		virtual ~ColorCubeScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private:
		AN::Object * m_cube{ nullptr };
		AN::Object * m_camera{ nullptr };
		AN::OrbitControls * m_orbitControls{ nullptr };

	private:
		AN::Shader * m_colorShader{ nullptr };
		AN::Geometry * m_cubeGeometry{ nullptr };
		AN::VertexArray * m_cubeVA{ nullptr };

	};

}
