#pragma once

namespace AN
{

	class Shader;

	class BuiltInResources
	{
	public:
		explicit BuiltInResources();
		~BuiltInResources();

		bool Initialize();

		Shader * GetDepthMapShader() const { return m_depthMapShader; }

	private:
		Shader * m_depthMapShader;

	};

}
