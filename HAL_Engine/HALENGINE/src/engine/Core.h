#pragma once

#ifdef HALENG_PLATFORM_WINDOWS
	#ifdef HALENG_BUILD_DLL
		#define HALENG_API __declspec(dllexport)
	#else
		#define HALENG_API __declspec(dllimport)
	#endif // HALENG_BUILD_DLL
#else
	#error Only supported on Windows
#endif // HALENG_PLATFORM_WINDOWS

#define BIT(x) (1 << x)