#pragma once

#include "Core.h"
#include "Mimou/Events/Event.h"
#include "Mimou/Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "Mimou/ImGui/ImGuiLayer.h"

// define a mimou application, all client
// extend this app

namespace Mimou {

	class MIMOU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		// inline function is a function that is expanded in line
		// when it is called. Inline function may increase efficiency
		// if it is small
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		//unique_ptr is a smart pointer that owns and manages 
		// another object through a pointer and disposes of 
		// that object when the unique_ptr goes out of scope.
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
		
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}



