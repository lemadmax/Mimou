#pragma once

// MM_PLATFORM_WINDOWS not clear yet, set in C/C++ preprocessor

#ifdef MM_PLATFORM_WINDOWS
	// Also in preprocessor, not in sandbox.
	#ifdef MM_BUILD_DLL
		#define MIMOU_API __declspec(dllexport)
	#else
		#define MIMOU_API __declspec(dllimport)
	#endif
#else
#error Mimou only support Windows!

#endif

#ifdef MM_ENABLE_ASSERTS
#define MM_CLIENT_ASSERT(x, ...) {if(!(x)) {MM_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#define MM_CORE_ASSERT(x, ...) {if(!(x)) {MM_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();}}
#else
#define MM_CLIENT_ASSERT(x, ...)
#define MM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define MM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)