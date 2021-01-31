#include "mmpch.h"

#include "Application.h"
#include "Log.h"
#include "Mimou/Events/MouseEvent.h"
#include "Mimou/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

#include <glad/glad.h>
#include "Mimou/Renderer/Renderer.h"

#include "Input.h"

#include "glm/glm.hpp"

namespace Mimou {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	

	Application::Application() {
		MM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// set eventcallbackfn of m_window to be OnEvent(event)
		// then when a event happen, data.eventcallbackfn is OnEvent(event)
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		
		m_ImGuiLayer = std::make_unique<ImGuiLayer>();

		
	}
	Application::~Application() {}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		//MM_CORE_TRACE("{0}", e);
		// each layer listen to this event (guanchazhe)
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::Run() {
		while (m_Running) {

			for (Layer* layer : m_LayerStack) 
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

}