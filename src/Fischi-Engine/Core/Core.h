#pragma once

#include <memory>

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

// Define Smart Pointers
namespace FischiEngine
{
    template <typename T>
    using Unique = std::unique_ptr<T>;

    template <typename T>
    using Shared = std::shared_ptr<T>;

    template <typename T>
    using Weak = std::weak_ptr<T>;

    template <typename T, typename... Args>
    constexpr Unique<T> CreateUnique(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    constexpr Shared<T> CreateShared(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

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
#define FISCHI_ABORT() abort()