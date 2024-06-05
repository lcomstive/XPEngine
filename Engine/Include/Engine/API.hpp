#pragma once

// Platform identification
#if defined(_WIN32)
	#define ENGINE_PLATFORM_WINDOWS
	#define ENGINE_PLATFORM_NAME "Windows"
#elif defined(__APPLE__)
	#define ENGINE_PLATFORM_APPLE

    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
        // iOS, tvOS, or watchOS device
		#define ENGINE_PLATFORM_iOS
		#define ENGINE_PLATFORM_NAME "iOS"
    #elif TARGET_OS_MAC
        // Other kinds of Apple platforms
		#define ENGINE_PLATFORM_MAC
		#define ENGINE_PLATFORM_NAME "Mac OS"
    #else
    #   error "Unknown Apple platform"
    #endif
#elif defined(__ANDROID__)
	#define ENGINE_PLATFORM_ANDROID
	#define ENGINE_PLATFORM_NAME "Android"
#elif defined(__EMSCRIPTEN__)
	#define ENGINE_PLATFORM_WEB
	#define ENGINE_PLATFORM_NAME "Web"
#elif defined(__linux__)
	#define ENGINE_PLATFORM_LINUX
	#define ENGINE_PLATFORM_NAME "Linux"
#elif defined(__unix__)
	#define ENGINE_PLATFORM_UNIX
	#define ENGINE_PLATFORM_NAME "Unix"
#else
	#error "Unknown platform"
#endif

#if defined(ENGINE_PLATFORM_WINDOWS) || \
	defined(ENGINE_PLATFORM_MAC) || \
	defined(ENGINE_PLATFORM_LINUX)
	#define ENGINE_PLATFORM_DESKTOP
#endif

#if defined(ENGINE_PLATFORM_iOS) || \
	defined(ENGINE_PLATFORM_ANDROID)
	#define ENGINE_PLATFORM_MOBILE
#endif

#if BUILD_SHARED_LIBS
	#if defined(_MSC_VER)
		#define ENGINE_EXPORT __declspec(dllexport)
		#define ENGINE_IMPORT __declspec(dllimport)
	#elif defined(__GNUC__)
		#define ENGINE_EXPORT __attribute__((visibility("default")))
		#define ENGINE_IMPORT
	#else
		#define ENGINE_EXPORT
		#define ENGINE_IMPORT
	#endif

	#if defined(ENGINE_EXPORT_DLL)
		#define EngineAPI ENGINE_EXPORT
	#else
		#define EngineAPI ENGINE_IMPORT
	#endif
#else
	#define ENGINE_EXPORT
	#define ENGINE_IMPORT
	#define EngineAPI
#endif

#ifndef ENGINE_VERSION_MAJOR
#define ENGINE_VERSION_MAJOR 0
#endif
#ifndef ENGINE_VERSION_MINOR
#define ENGINE_VERSION_MINOR 0
#endif
#ifndef ENGINE_VERSION_PATCH
#define ENGINE_VERSION_PATCH 0
#endif
#ifndef ENGINE_VERSION_REV
#define ENGINE_VERSION_REV 0
#endif
#ifndef ENGINE_VERSION_BRANCH
#define ENGINE_VERSION_BRANCH ""
#endif

// Silence errors
#pragma warning(disable : 4251)