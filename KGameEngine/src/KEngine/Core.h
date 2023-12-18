#pragma once

#ifdef KE_PLATFORM_WINDOWS
	#ifdef KE_BUILD_DLL
		#define KENGINE_API __declspec(dllexport)
	#else
		#define KENGINE_API __declspec(dllimport)
	#endif // KE_BUILD_DLL
#else
	#error KEngine Only Support Windows!
#endif

#define BIT(x) (1 << x)