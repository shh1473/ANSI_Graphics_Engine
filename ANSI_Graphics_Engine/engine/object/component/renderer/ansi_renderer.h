#pragma once

#include "object/component/ansi_component.h"
#include "object/component/renderer/input_param/ansi_input_param.h"
#include "object/component/renderer/output_param/ansi_output_param.h"
#include "object/component/renderer/raster_param/ansi_raster_param.h"
#include "object/component/renderer/shader_param/ansi_shader_param.h"

namespace AN
{

	class Object;

	class Renderer : public Component
	{
	public:
		explicit Renderer(Object * object);

		bool OnRender();

		InputParam * Input() { if (!m_inputParam) { m_inputParam = new InputParam(); } return m_inputParam; }
		OutputParam * Output() { if (!m_outputParam) { m_outputParam = new OutputParam(); } return m_outputParam; }
		RasterParam * Raster() { if (!m_rasterParam) { m_rasterParam = new RasterParam(); } return m_rasterParam; }
		ShaderParam * Shader() { if (!m_shaderParam) { m_shaderParam = new ShaderParam(); } return m_shaderParam; }

	private:
		InputParam * m_inputParam;
		OutputParam * m_outputParam;
		RasterParam * m_rasterParam;
		ShaderParam * m_shaderParam;

	};

	class ForwardRenderer : public Renderer
	{
	public:
		explicit ForwardRenderer(Object * owner);
		virtual ~ForwardRenderer();

	};

	class DeferredRenderer : public Renderer
	{
	public:
		explicit DeferredRenderer(Object * owner);
		virtual ~DeferredRenderer();

	};

	class PackingRenderer : public Renderer
	{
	public:
		explicit PackingRenderer(Object * owner);
		virtual ~PackingRenderer();

	};

	class ComputeRenderer : public Renderer
	{
	public:
		explicit ComputeRenderer(Object * owner);
		virtual ~ComputeRenderer();

	};

}