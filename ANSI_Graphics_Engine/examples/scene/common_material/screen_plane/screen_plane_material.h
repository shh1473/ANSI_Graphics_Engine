#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ScreenPlaneMaterial : public AN::Material
	{
	public:
		explicit ScreenPlaneMaterial(AN::Shader * shader, unsigned textureId, const glm::vec4 & viewport = glm::vec4(0.0f, 0.0f, 100.0f, 100.0f));

		bool OnUpdateUniforms() override;

		void SetDiffuseColor(const glm::vec3 & color) { m_diffuseColor = glm::vec4(color.r, color.g, color.b, m_diffuseColor.a); }

	private:
		glm::vec4 m_viewport;
		AN::StateChecker<glm::vec2> m_cameraSize;

	};

}
