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