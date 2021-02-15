#pragma once

#ifdef MM_PLATFORM_WINDOWS

// extern: declare a variable or a function, the definition of this function or variable
// is in another file. The complier will have to search
// the definition in another file.

extern Mimou::Application* Mimou::CreateApplication();

int main(int argc, char** argv) {
	Mimou::Log::Init();
	MM_CORE_WARN("Initialized Log!");
	MM_CLIENT_INFO("Hello Mimou!");
	auto app = Mimou::CreateApplication();
	app->Run();
	delete app;
}

#endif