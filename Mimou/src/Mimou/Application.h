#pragma once

#include "Core.h"
#include "Events/Event.h"

// define a mimou application, all client
// extend this app

namespace Mimou {

	class MIMOU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}



