#pragma once

#ifdef MM_PLATFORM_WINDOWS

// extern: declare a variable or a function, the definition of this function or variable
// is in another file. The complier will have to search
// the definition in another file.

extern Mimou::Application* Mimou::CreateApplication();

int main(int argc, char** argv) {
	Mimou::Log::Init();
	
	MM_PROFILE_BEGIN_SESSION("Startup", "MimouProfile-Startup.json");
	auto app = Mimou::CreateApplication();
	MM_PROFILE_END_SESSION();
	
	MM_PROFILE_BEGIN_SESSION("Runtime", "MimouProfile-Runtime.json");
	app->Run();
	MM_PROFILE_END_SESSION();

	MM_PROFILE_BEGIN_SESSION("Shutdown", "MimouProfile-Shutdown.json");
	delete app;
	MM_PROFILE_END_SESSION();

}

#endif