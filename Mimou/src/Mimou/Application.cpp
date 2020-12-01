#include "mmpch.h"

#include "Application.h"
#include "Log.h"
#include "Mimou/Events/MouseEvent.h"
#include "Mimou/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace Mimou {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
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
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {
		m_Running = false;
		return true;
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
			m_Window->OnUpdate();
		}
	}

}