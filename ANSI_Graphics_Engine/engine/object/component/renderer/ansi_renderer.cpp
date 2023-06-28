#include "ansi_renderer.h"

#include "core/render/ansi_render.h"
#include "resource/shader/ansi_shader.h"
#include "object/component/renderer/input_param/ansi_input_param.h"
#include "object/component/renderer/dispatch_param/ansi_dispatch_param.h"
#include "object/component/renderer/shader_param/ansi_shader_param.h"
#include "object/component/renderer/shader_param/depth_map_shader/ansi_depth_map_shader.h"

namespace AN
{

	Renderer::Renderer(Object * object, ShaderParam * shaderParam, bool isCastShadow) :
		Component(object),
		m_inputParam((
			shaderParam->GetShader()->GetType() != RenderType::Deferred &&
			shaderParam->GetShader()->GetType() != RenderType::Compute) ? new InputParam() : nullptr),
		m_dispatchParam((
			shaderParam->GetShader()->GetType() != RenderType::Deferred &&
			shaderParam->GetShader()->GetType() == RenderType::Compute) ? new DispatchParam() : nullptr),
		m_shaderParam(shaderParam),
		m_depthMapShader(isCastShadow && (
			shaderParam->GetShader()->GetType() == RenderType::Forward ||
			shaderParam->GetShader()->GetType() == RenderType::Packing) ? new DepthMapShader() : nullptr)
	{
		Core::GetRender()->AddRenderer(this, m_shaderParam->GetShader()->GetType());
	}

	Renderer::~Renderer()
	{
		Core::GetRender()->RemoveRenderer(this, m_shaderParam->GetShader()->GetType());
		AN_DELETE(m_inputParam);
		AN_DELETE(m_dispatchParam);
		AN_DELETE(m_shaderParam);
		AN_DELETE(m_depthMapShader);
	}

}
