#pragma once

#ifdef MM_PLATFORM_WINDOWS
	#ifdef MM_BUILD_DLL
		#define MIMOU_API __declspec(dllexport)
	#else
		#define MIMOU_API __declspec(dllimport)
	#endif
#else
#error Mimou only support Windows!

#endif