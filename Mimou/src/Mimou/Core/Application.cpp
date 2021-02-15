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
		m_Window->SetVSync(1);
		
		Renderer::Init();
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
	}
	Application::~Application() {}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResized));
		//MM_CORE_TRACE("{0}", e);
		// each layer listen to this event (guanchazhe)
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::Run() {
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
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

	bool Application::OnWindowResized(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		// use setviewport to resize the buffer so that
		// the renderer will render the whole window.
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
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