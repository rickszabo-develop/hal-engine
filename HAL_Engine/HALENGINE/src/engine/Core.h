#pragma once

#ifdef HALENG_PLATFORM_WINDOWS
	#ifdef HALENG_DYNAMIC_LINK
		#ifdef HALENG_BUILD_DLL
			#define HALENG_API __declspec(dllexport)
		#else
			#define HALENG_API __declspec(dllimport)
		#endif // HALENG_BUILD_DLL
	#else
		#define HALENG_API 
	#endif
#else
	#error Only supported on Windows
#endif // HALENG_PLATFORM_WINDOWS

#ifdef HALENG_ENABLE_ASSERTS
	#define HALENG_ASSERT(x, ...) { if(!(x)) { HALENG_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HALENG_CORE_ERROR(x, ...) { if(!(x)) { HALENG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HALENG_ASSERT(x, ...)
	#define HALENG_CORE_ERROR(x, ...)
#endif

#define BIT(x) (1 << x)