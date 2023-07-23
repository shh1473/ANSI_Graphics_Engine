#include "ansi_render.h"

#include "core/render/input_executor/ansi_input_executor.h"
#include "core/render/raster_executor/ansi_raster_executor.h"
#include "core/render/shader_executor/ansi_shader_executor.h"
#include "core/render/output_executor/ansi_output_executor.h"
#include "core/render/built_in_resources/ansi_built_in_resources.h"
#include "object/component/camera/ansi_camera.h"
#include "object/component/camera/output_param/g_buffer_output/ansi_g_buffer_output.h"
#include "object/component/renderer/ansi_renderer.h"
#include "object/component/renderer/shader_param/depth_map_shader/ansi_depth_map_shader.h"

namespace AN
{

	Render::Render() :
		m_currentCamera(nullptr),
		m_inputExecutor(new InputExecutor()),
		m_rasterExecutor(new RasterExecutor()),
		m_shaderExecutor(new ShaderExecutor()),
		m_outputExecutor(new OutputExecutor()),
		m_builtInResources(new BuiltInResources()),
		m_cameras(),
		m_renderers()
	{

	}

	Render::~Render()
	{
		AN_DELETE(m_inputExecutor);
		AN_DELETE(m_rasterExecutor);
		AN_DELETE(m_shaderExecutor);
		AN_DELETE(m_outputExecutor);
	}

	bool Render::Initialize()
	{
		AN_CHECK(m_builtInResources->Initialize());
		return true;
	}

	void Render::Reset()
	{
		m_inputExecutor->Reset();
		m_rasterExecutor->Reset();
		m_shaderExecutor->Reset();
		m_outputExecutor->Reset();
	}

	bool Render::OnRender()
	{
		// Depth Map
		if (m_renderers[static_cast<unsigned>(RenderType::Forward)].size() > 0 ||
			m_renderers[static_cast<unsigned>(RenderType::Packing)].size() > 0)
		{
			for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::Light)])
			{
				if (!camera->GetIsEnabled()) { continue; }
				m_currentCamera = camera;
				AN_CHECK(m_rasterExecutor->Apply(camera->Raster()));
				AN_CHECK(m_outputExecutor->Apply(camera->Output()));
				for (const auto & renderer : m_renderers[static_cast<unsigned>(RenderType::Forward)])
				{
					if (renderer->GetDepthMapShader())
					{
						AN_CHECK(m_inputExecutor->Apply(renderer->Input()));
						AN_CHECK(m_shaderExecutor->Apply(renderer->GetDepthMapShader()));
						AN_CHECK(Draw());
					}
				}
				for (const auto & renderer : m_renderers[static_cast<unsigned>(RenderType::Packing)])
				{
					if (renderer->GetDepthMapShader())
					{
						AN_CHECK(m_inputExecutor->Apply(renderer->Input()));
						AN_CHECK(m_shaderExecutor->Apply(renderer->GetDepthMapShader()));
						AN_CHECK(Draw());
					}
				}
			}
		}
		// Packing
		if (m_renderers[static_cast<unsigned>(RenderType::Packing)].size() > 0)
		{
			for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::Camera)])
			{
				if (!camera->GetIsEnabled()) { continue; }
				m_currentCamera = camera;
				AN_CHECK(m_rasterExecutor->Apply(camera->Raster()));
				AN_CHECK(m_outputExecutor->Apply(camera->GetGBufferOutput()));
				for (const auto & renderer : m_renderers[static_cast<unsigned>(RenderType::Packing)])
				{
					AN_CHECK(m_inputExecutor->Apply(renderer->Input()));
					AN_CHECK(m_shaderExecutor->Apply(renderer->Shader()));
					AN_CHECK(Draw());
				}
			}
		}
		// Deferred
		if (m_renderers[static_cast<unsigned>(RenderType::Deferred)].size() > 0)
		{
			for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::Camera)])
			{
				if (!camera->GetIsEnabled()) { continue; }
				m_currentCamera = camera;
				for (const auto & renderer : m_renderers[static_cast<unsigned>(RenderType::Deferred)])
				{
					AN_CHECK(m_inputExecutor->Apply(renderer->Dispatch()));
					AN_CHECK(m_shaderExecutor->Apply(renderer->Shader()));
					// Set output texture uniform from camera
					// renderer->Shader()->SetUniform1i("output", camera->GetGBufferOutput()->GetDeferredOutputTextureId());
					AN_CHECK(Draw());
				}
			}
		}
		// Forward
		if (m_renderers[static_cast<unsigned>(RenderType::Forward)].size() > 0)
		{
			for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::Camera)])
			{
				if (!camera->GetIsEnabled()) { continue; }
				m_currentCamera = camera;
				AN_CHECK(m_rasterExecutor->Apply(camera->Raster()));
				AN_CHECK(m_outputExecutor->Apply(camera->Output()));
				for (const auto & renderer : m_renderers[static_cast<unsigned>(RenderType::Forward)])
				{
					AN_CHECK(m_inputExecutor->Apply(renderer->Input()));
					AN_CHECK(m_shaderExecutor->Apply(renderer->Shader()));
					AN_CHECK(Draw());
				}
			}
		}
		// Compute
		if (m_renderers[static_cast<unsigned>(RenderType::Compute)].size() > 0)
		{
			for (const auto & renderer : m_renderers[static_cast<unsigned>(RenderType::Compute)])
			{
				AN_CHECK(m_inputExecutor->Apply(renderer->Dispatch()));
				AN_CHECK(m_shaderExecutor->Apply(renderer->Shader()));
				AN_CHECK(Draw());
			}
		}
		// Use a built-in shader to copy the last result texture of compute shaders into main framebuffer

		return true;
	}

	bool Render::Draw()
	{
		if (m_inputExecutor->GetVertexCount() == 0)
		{
			GL_CHECK(glDispatchCompute(
				m_inputExecutor->GetDispatchSize().x,
				m_inputExecutor->GetDispatchSize().y,
				m_inputExecutor->GetDispatchSize().z));
		}
		else if (m_inputExecutor->GetIndexCount() == 0)
		{
			GL_CHECK(glDrawArrays(static_cast<unsigned>(m_inputExecutor->GetPrimitiveTopology()), 0, m_inputExecutor->GetVertexCount()));
		}
		else
		{
			GL_CHECK(glDrawElements(static_cast<unsigned>(m_inputExecutor->GetPrimitiveTopology()), m_inputExecutor->GetIndexCount(), GL_UNSIGNED_INT, nullptr));
		}

		return true;
	}

}