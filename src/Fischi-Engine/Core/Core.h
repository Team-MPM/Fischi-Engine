#pragma once

#include <cstdint>
#include <memory>

// Warning

// classes from stdlib need to have dll-interface to be used by clients
#pragma warning(disable: 4251)

// Detect Platform
#if defined(_WIN32) || defined(_WIN64)
    #ifndef FISCHI_PLATFORM_WINDOWS
        #define FISCHI_PLATFORM_WINDOWS
    #endif
    #define _CRT_SECURE_NO_WARNINGS
#elif defined(__linux__)
    #ifndef FISCHI_PLATFORM_LINUX
        #define FISCHI_PLATFORM_LINUX
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define FISCHI_PLATFORM_MACOS
    #error "MacOS is not supported!"
#else
    #error "Unknown platform!"
#endif

// Detect Compiler
#if defined(__clang__)
    #define FISCHI_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define FISCHI_COMPILER_GCC
#elif defined(_MSC_VER)
    #define FISCHI_COMPILER_MSVC
#elif defined(__INTEL_COMPILER)
    #define FISCHI_COMPILER_INTEL
#else
    #error "Unknown compiler!"
#endif

// Dll Export/Import
#if defined(FISCHI_COMPILER_MSVC)
    #if defined(FISCHI_BUILD_DLL)
        #define FISCHI_API __declspec(dllexport)
    #else
        #define FISCHI_API __declspec(dllimport)
    #endif
#elif defined(FISCHI_COMPILER_GCC) || defined(FISCHI_COMPILER_CLANG)
    #if defined(FISCHI_BUILD_DLL)
        #define FISCHI_API __attribute__((visibility("default")))
    #else
        #define FISCHI_API
    #endif
#else
    #define FISCHI_API 
    #warning "FISCHI_API defined empty, add support for whatever your compiler need!"
#endif

// Define common macros
#define BIT(x) (1 << x)

// Define Asserts
#if defined(FISCHI_DIST)
    #define FISCHI_DEBUG_BREAK()
#elif defined(FISCHI_PLATFORM_WINDOWS)
    #define FISCHI_DEBUG_BREAK() __debugbreak()
#elif defined(FISCHI_PLATFORM_LINUX)
    #include <csignal>
    #define FISCHI_DEBUG_BREAK() raise(SIGTRAP)
#else
    #error "Debug break not supported on this platform!"
#endif

#define FISCHI_ABORT() Log::Fatal("Application was aborted at: {0}: {1}", __FILE__, __LINE__); abort()