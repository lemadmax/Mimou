#pragma once

#include "Mimou/Core/Layer.h"

#include "Mimou/Events/KeyEvent.h"
#include "Mimou/Events/MouseEvent.h"
#include "Mimou/Events/ApplicationEvent.h"

namespace Mimou {
	
	class MIMOU_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}

