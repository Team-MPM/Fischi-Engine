#pragma once

#include <Core/Memory/Memory.h>

// Detect Platform
#if defined(_WIN32) || defined(_WIN64)
    #define FISCHI_PLATFORM_WINDOWS
    #define _CRT_SECURE_NO_WARNINGS
#elif defined(__linux__)
    #define FISCHI_PLATFORM_LINUX
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

// Define common macros
#define BIT(x) (1 << x)

// Define Asserts
#if defined(FISCHI_DIST)
    #define FISCHI_DEBUG_BREAK()
#elif defined(FISCHI_PLATFORM_WINDOWS)
    #define FISCHI_DEBUG_BREAK() __debugbreak()
#elif defined(FISCHI_PLATFORM_LINUX)
    #include <signal.h>
    #define FISCHI_DEBUG_BREAK() raise(SIGTRAP)
#else
    #error "Debug break not supported on this platform!"
#endif

// Define Abort
#define FISCHI_ABORT() Log::Fatal("Application was aborted at: {0}: {1}", __FILE__, __LINE__); abort()