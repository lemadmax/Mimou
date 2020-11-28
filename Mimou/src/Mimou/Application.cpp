#include "Application.h"
#include "Log.h"
#include "Mimou/Events/MouseEvent.h"
#include "Mimou/Events/ApplicationEvent.h"

namespace Mimou {

	Application::Application() {}
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
		while (true);
	}

}