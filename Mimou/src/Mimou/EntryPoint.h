#pragma once

#ifdef MM_PLATFORM_WINDOWS

extern Mimou::Application * Mimou::CreateApplication();

int main(int argc, char** argv) {

	cout << "hello Mimou!" << endl;
	auto app = Mimou::CreateApplication();
	app->Run();
	delete app;
}

#endif