#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class HSAmbientLightScene : public AN::Scene
	{
	public:
		explicit HSAmbientLightScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private:
		static const glm::vec3 m_DefaultAmbientLightUpColor;
		static const glm::vec3 m_DefaultAmbientLightDownColor;

	private: /* === Gui === */
		bool m_isWireframe;
		glm::vec3 m_ambientLightUpColor;
		glm::vec3 m_ambientLightDownColor;

	private: /* === Objects === */
		AN::Object * m_rgrat{ nullptr };
		AN::Object * m_ambientLight{ nullptr };
		AN::Object * m_camera{ nullptr };
		AN::OrbitControls * m_orbitControls{ nullptr };

	private: /* === Resources === */
		AN::Shader * m_hsAmbientLightShader{ nullptr };

		AN::Geometry * m_rgratGeometry{ nullptr };
		AN::VertexArray * m_rgratVA{ nullptr };

	};

}
