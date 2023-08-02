#pragma once

namespace AN
{

	class Shader;
	class DepthMapMaterial;

	class BuiltIn
	{
	public:
		explicit BuiltIn();
		~BuiltIn();

		bool Initialize();

		DepthMapMaterial * GetDepthMapMaterial() const { return m_depthMapMaterial; }

	private:
		Shader * m_depthMapShader;
		DepthMapMaterial * m_depthMapMaterial;

	};

}
