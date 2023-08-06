#pragma once

namespace AN
{

	class Shader;
	class DepthSpotMaterial;
	class DepthPointMaterial;

	class BuiltIn
	{
	public:
		explicit BuiltIn();
		~BuiltIn();

		bool Initialize();

		DepthSpotMaterial * GetDepthSpotMaterial() const { return m_depthSpotMaterial; }
		DepthPointMaterial * GetDepthPointMaterial() const { return m_depthPointMaterial; }

	private:
		Shader * m_depthSpotShader;
		Shader * m_depthPointShader;

		DepthSpotMaterial * m_depthSpotMaterial;
		DepthPointMaterial * m_depthPointMaterial;

	};

}
