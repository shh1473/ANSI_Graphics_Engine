#pragma once

#include "object/component/renderer/input_param/ansi_input_param.h"
#include "object/component/renderer/dispatch_param/ansi_dispatch_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace AN
{

	class InputExecutor
	{
	public:
		explicit InputExecutor();

		bool Apply(InputParam * param);
		bool Apply(DispatchParam * param);
		void Reset();

		unsigned GetVertexCount() const { return m_vertexCount; }
		unsigned GetIndexCount() const { return m_indexCount; }
		glm::uvec3 GetDispatchSize() const { return m_dispatchSize; }
		PrimitiveTopology GetPrimitiveTopology() const { return m_primitiveTopology; }

	private:
		unsigned m_vertexCount;
		unsigned m_indexCount;
		glm::uvec3 m_dispatchSize;
		PrimitiveTopology m_primitiveTopology;
		StateChecker<bool> m_isEnableDepthTest;
		StateChecker<bool> m_isEnableDepthWrite;
		StateChecker<unsigned> m_vertexArrayId;
		StateChecker<unsigned> m_indexBufferId;

	};

}
