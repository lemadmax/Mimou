#pragma once

#include "Mimou/Core/Core.h"
#include "Mimou/Events/Event.h"
#include "Mimou/Core/TimeStep.h"

namespace Mimou {

	class MIMOU_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}


