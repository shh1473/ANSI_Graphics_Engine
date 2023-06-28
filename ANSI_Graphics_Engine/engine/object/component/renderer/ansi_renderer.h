#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class InputParam;
	class DispatchParam;
	class ShaderParam;
	class DepthMapShader;

	class Renderer : public Component
	{
	public:
		explicit Renderer(Object * object, ShaderParam * shaderParam, bool isCastShadow = false);
		virtual ~Renderer();

		InputParam * Input() const { return m_inputParam; }
		DispatchParam * Dispatch() const { return m_dispatchParam; }
		ShaderParam * Shader() const { return m_shaderParam; }
		DepthMapShader * GetDepthMapShader() const { return m_depthMapShader; }

	private:
		InputParam * m_inputParam;
		DispatchParam * m_dispatchParam;
		ShaderParam * m_shaderParam;
		DepthMapShader * m_depthMapShader;

	};

}