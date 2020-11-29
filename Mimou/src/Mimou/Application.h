#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

// define a mimou application, all client
// extend this app

namespace Mimou {

	class MIMOU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		//unique_ptr is a smart pointer that owns and manages 
		// another object through a pointer and disposes of 
		// that object when the unique_ptr goes out of scope.
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}



