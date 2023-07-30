#pragma once

#include <ansi_graphics_engine.h>

namespace Example
{

	class TextureMaterial : public AN::Material
	{
	public:
		explicit TextureMaterial(AN::Shader * shader);

		bool OnUpdateUniforms() override;

		void SetDiffuseMap(unsigned textureId) { m_textureIds[0] = textureId; }

	};

}
