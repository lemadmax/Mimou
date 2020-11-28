#pragma once

#ifdef MM_PLATFORM_WINDOWS

// extern: the definition of this function or variable
// is in another file. The complier will have to search
// the definition in another file.

extern Mimou::Application * Mimou::CreateApplication();

int main(int argc, char** argv) {
	Mimou::Log::Init();
	MM_CORE_WARN("Initialized Log!");
	int a = 5;
	MM_CLIENT_INFO("Hello Mimou! Var = {0}", a);
	auto app = Mimou::CreateApplication();
	app->Run();
	delete app;
}

#endif