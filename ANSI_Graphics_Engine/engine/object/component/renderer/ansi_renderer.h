#pragma once

#include "object/component/ansi_component.h"

namespace AN
{

	class InputParam;
	class DispatchParam;
	class Material;

	class Renderer : public Component
	{
	public:
		explicit Renderer(Object * object, Material * material);
		virtual ~Renderer();

		bool GetIsCastShadow() const { return m_isCastShadow; }
		bool GetIsReceiveShadow() const { return m_isReceiveShadow; }
		Material * GetMaterial() const { return m_material; }
		InputParam * GetInput() const { return m_inputParam; }
		DispatchParam * GetDispatch() const { return m_dispatchParam; }

	private:
		bool m_isCastShadow;
		bool m_isReceiveShadow;
		Material * m_material;
		InputParam * m_inputParam;
		DispatchParam * m_dispatchParam;

	};

}