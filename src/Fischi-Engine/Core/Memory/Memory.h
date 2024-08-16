#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>

#include "LinearBlockAllocator.h"

namespace FischiEngine
{
    template <typename T>
    using Unique = std::unique_ptr<T>;

    template <typename T>
    using Shared = std::shared_ptr<T>;

    template <typename T>
    using Weak = std::weak_ptr<T>;
    
    template <typename T>
    using Vector = std::vector<T>;

    enum class MemoryType
    {
        Unique,
        Shared,
        Heap,
        Arena,
        Pool,
        Vector,
        LinearBlockAllocator
    };

    enum class MemoryUsage
    {
        Other,
        Application,
        Project,
        Scene,
        Window,
        Renderer,
        Game,
    };

    class FISCHI_API Memory
    {
    public:
        template <typename T, typename... Args>
        static constexpr Unique<T> CreateUnique(MemoryUsage usage, Args&&... args)
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        static constexpr Shared<T> CreateShared(const MemoryUsage usage, Args&&... args)
        {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        static T* AllocateHeap(const MemoryUsage usage, Args&&... args)
        {
            return new T(std::forward<Args>(args)...);
        }

        template <typename T>
        static void FreeHeap(T* ptr, const MemoryUsage usage)
        {
            delete ptr;
        }

        static std::unordered_map<MemoryUsage, size_t> GetMemoryUsages();
        static std::unordered_map<MemoryType, size_t> GetMemoryTypes();

        static LinearBlockAllocator CreateLinearBlockAllocator(size_t blockSize, size_t blockCount, MemoryUsage usage);
    private:
        static std::unordered_map<MemoryUsage, size_t> m_MemoryUsages;
        static std::unordered_map<MemoryType, size_t> m_MemoryTypes;
        static std::mutex m_Mutex;
    };
}
