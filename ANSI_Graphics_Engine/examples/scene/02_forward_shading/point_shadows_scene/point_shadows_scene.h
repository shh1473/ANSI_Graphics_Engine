#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{

	class PointShadowsScene : public ExampleScene
	{
	public:
		explicit PointShadowsScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private:
		void UpdateLightRotation();

	private: /* === Gui === */
		bool m_isAnimateRotation;
		float m_lightRadius;
		float m_lightRotation;

	private: /* === Object === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_box{ nullptr };
		AN::Object * m_pointLights[3]{ nullptr, };
		AN::Object * m_camera{ nullptr };

		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resource === */
		AN::Shader * m_pointShadows3Shader{ nullptr };

		AN::VertexArray * m_rgratVA{ nullptr };
		AN::VertexArray * m_shadowCastSphereVA{ nullptr };
		AN::VertexArray * m_boxVA{ nullptr };

	};

}
