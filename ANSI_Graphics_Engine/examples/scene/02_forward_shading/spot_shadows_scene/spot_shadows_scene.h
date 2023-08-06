#pragma once

#include <ansi_graphics_engine.h>

#include "../../example_scene.h"

namespace Example
{

	class SpotShadowsScene : public ExampleScene
	{
	public:
		explicit SpotShadowsScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private:
		void UpdateLightDistance();

	private: /* === Gui === */
		bool m_isVisibleShadowMaps;
		float m_lightRadius;
		float m_lightAngle;
		float m_lightSmoothRange;
		float m_lightRotation;
		float m_lightDistance;
		glm::vec3 m_lightRotationXs;

	private: /* === Object === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_plane{ nullptr };
		AN::Object * m_shadowPlanes[3]{ nullptr };
		AN::Object * m_lightGroup{ nullptr };
		AN::Object * m_spotLights[3]{ nullptr, };
		AN::Object * m_camera{ nullptr };

		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resource === */
		AN::Shader * m_spotShadows3Shader{ nullptr };
		AN::Shader * m_screenPlaneShader{ nullptr };

		AN::VertexArray * m_rgratVA{ nullptr };
		AN::VertexArray * m_floorPlaneVA{ nullptr };
		AN::VertexArray * m_shadowMapPlaneVA{ nullptr };

	};

}
