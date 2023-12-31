#pragma once

#ifdef KE_PLATFORM_WINDOWS
	#if KE_DYNAMIC_LINK
		#ifdef KE_BUILD_DLL
			#define KENGINE_API __declspec(dllexport)
		#else
			#define KENGINE_API __declspec(dllimport)
		#endif // KE_BUILD_DLL
	#else
		#define KENGINE_API
	#endif
#else
	#error KEngine Only Support Windows!
#endif

#ifdef KE_ENABLE_ASSERTS
	#define KE_ASSERT(x, ...) {if(!(x)) {KE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define KE_CORE_ASSERT(x, ...) {if(!(x)) {KE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define KE_ASSERT(x, ...) 
	#define KE_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)


#define KE_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)