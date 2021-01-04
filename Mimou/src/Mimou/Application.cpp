#include "mmpch.h"



#include "Application.h"
#include "Log.h"
#include "Mimou/Events/MouseEvent.h"
#include "Mimou/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

#include <glad/glad.h>

#include "Input.h"

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
	}
	Application::~Application() {}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		MM_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::Run() {
		MouseMovedEvent e(3.23, 1.33);
		WindowResizeEvent e1(1232, 332);
		if (!e.IsInCategory(EventCategoryApplication)) {
			MM_CLIENT_ERROR("not an application event");
		}
		if (e.IsInCategory(EventCategoryMouse)) {
			MM_CLIENT_TRACE(e);
		}
		MM_CLIENT_TRACE(e1);
		while (m_Running) {
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack) 
				layer->OnUpdate();
			auto [x, y] = Input::GetMousePos();
			bool A = Input::IsKeyPressed(GLFW_KEY_A);
			bool ML = Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
			MM_CORE_TRACE("{0}, {1}", x, y);
			if (A) {
				MM_CORE_WARN("A is pressed!!!");
			}
			if (ML) {
				MM_CORE_WARN("Left mouse button is pressed!!!");
			}
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