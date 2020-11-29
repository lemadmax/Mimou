#include "mmpch.h"

#include "Application.h"
#include "Log.h"
#include "Mimou/Events/MouseEvent.h"
#include "Mimou/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace Mimou {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {}

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