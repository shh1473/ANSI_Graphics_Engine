#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class ColorMaterial : public AN::Material
	{
	public:
		explicit ColorMaterial(AN::Shader * shader);

		bool OnUpdateUniforms() override;

		void SetDiffuseColor(const glm::vec3 & color) { m_diffuseColor = glm::vec4(color.r, color.g, color.b, m_diffuseColor.a); }
		void SetFillMode(AN::FillMode fillMode) { m_fillMode = fillMode; }
		void SetCullMode(AN::CullMode cullMode) { m_cullMode = cullMode; }

	};

}
