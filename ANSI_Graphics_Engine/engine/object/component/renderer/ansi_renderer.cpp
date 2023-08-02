#include "ansi_renderer.h"

#include "core/render/ansi_render.h"
#include "core/render/input_executor/input_param/ansi_input_param.h"
#include "core/render/input_executor/dispatch_param/ansi_dispatch_param.h"
#include "core/render/shader_executor/material/ansi_material.h"
#include "resource/vertex_array/ansi_vertex_array.h"
#include "object/ansi_object.h"

namespace AN
{

	Renderer::Renderer(Object * object, VertexArray * vertexArray, Material * material) :
		Component(object),
		m_isCastShadow(false),
		m_isReceiveShadow(false),
		m_material(material),
		m_inputParam((
			m_material->m_renderType != RenderType::Deferred &&
			m_material->m_renderType != RenderType::Compute) ? new InputParam() : nullptr),
		m_dispatchParam((
			m_material->m_renderType != RenderType::Deferred &&
			m_material->m_renderType == RenderType::Compute) ? new DispatchParam() : nullptr)
	{
		Core::GetRender()->AddRenderer(this, m_material->m_renderType);

		m_inputParam->SetVertexArray(vertexArray);
		m_material->m_transform = object->GetTransform();
	}

	Renderer::~Renderer()
	{
		Core::GetRender()->RemoveRenderer(this, m_material->m_renderType);

		AN_DELETE(m_material);
		AN_DELETE(m_inputParam);
		AN_DELETE(m_dispatchParam);
	}

}
