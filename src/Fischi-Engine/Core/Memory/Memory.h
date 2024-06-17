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

    class Memory
    {
    public:
        template <typename T, typename... Args>
        static constexpr Unique<T> CreateUnique(MemoryUsage usage, Args&&... args)
        {
            auto deleter = [usage](const T* ptr)
            {
                std::lock_guard lock(m_Mutex);
                m_MemoryTypes[MemoryType::Unique] -= sizeof(T);
                m_MemoryUsages[usage] -= sizeof(T);
                delete ptr;
            };

            Unique<T> ptr(new T(std::forward<Args>(args)...), deleter);

            {
                std::lock_guard lock(m_Mutex);
                m_MemoryTypes[MemoryType::Unique] += sizeof(T);
                m_MemoryUsages[usage] += sizeof(T);
            }

            return ptr;
        }

        template <typename T, typename... Args>
        static constexpr Shared<T> CreateShared(const MemoryUsage usage, Args&&... args)
        {
            auto deleter = [usage](const T* ptr)
            {
                {
                    #ifndef FISCHI_PLATFORM_LINUX // TOTO: WTF IS THIS BULLSHIT NOT WORKING ON LINUX ??
                    std::lock_guard lock(m_Mutex);
                    m_MemoryTypes[MemoryType::Shared] -= sizeof(T);
                    m_MemoryUsages[usage] -= sizeof(T);
                    #endif
                }
                delete ptr;
            };

            Shared<T> ptr(new T(std::forward<Args>(args)...), deleter);
            {
                std::lock_guard lock(m_Mutex);
                m_MemoryTypes[MemoryType::Shared] += sizeof(T);
                m_MemoryUsages[usage] += sizeof(T);
            }

            return ptr;
        }

        template <typename T, typename... Args>
        static T* AllocateHeap(const MemoryUsage usage, Args&&... args)
        {
            T* ptr = new T(std::forward<Args>(args)...);

            {
                std::lock_guard lock(m_Mutex);
                m_MemoryTypes[MemoryType::Heap] += sizeof(T);
                m_MemoryUsages[usage] += sizeof(T);
            }

            return ptr;
        }

        template <typename T>
        static void FreeHeap(T* ptr, const MemoryUsage usage)
        {
            {
                std::lock_guard lock(m_Mutex);
                m_MemoryTypes[MemoryType::Heap] -= sizeof(T);
                m_MemoryUsages[usage] -= sizeof(T);
            }
            delete ptr;
        }

        template <typename T>
        class TrackingAllocator : public std::allocator<T>
        {
        public:
            MemoryUsage Usage;

            TrackingAllocator(MemoryUsage usage = MemoryUsage::Other) : Usage(usage)
            {
            }

            template <typename U>
            TrackingAllocator(const TrackingAllocator<U>& other) : Usage(other.Usage)
            {
            }


            template <typename U>
            struct rebind
            {
                typedef TrackingAllocator<U> other;
            };

            T* allocate(std::size_t n)
            {
                {
                    std::lock_guard lock(m_Mutex);
                    m_MemoryTypes[MemoryType::Vector] += sizeof(T);
                    m_MemoryUsages[Usage] += sizeof(T);
                }
                return std::allocator<T>::allocate(n);
            }

            void deallocate(T* p, std::size_t n)
            {
                {
                    std::lock_guard lock(m_Mutex);
                    m_MemoryTypes[MemoryType::Vector] -= sizeof(T);
                    m_MemoryUsages[Usage] -= sizeof(T);
                }
                std::allocator<T>::deallocate(p, n);
            }
        };

        template <typename T>
        using Vector = std::vector<T, TrackingAllocator<T>>;

        template <typename T>
        static Vector<T> CreateVector(MemoryUsage usage, size_t capacity = 0)
        {
            std::vector<T, TrackingAllocator<T>> vec{TrackingAllocator<T>(usage)};
            vec.reserve(capacity);
            return vec;
        }

        

        static void LogMemoryUsage();

        static std::unordered_map<MemoryUsage, size_t> GetMemoryUsages();
        static std::unordered_map<MemoryType, size_t> GetMemoryTypes();

        static LinearBlockAllocator CreateLinearBlockAllocator(size_t blockSize, size_t blockCount, MemoryUsage usage)
        {
            {
                std::lock_guard lock(m_Mutex);
                m_MemoryTypes[MemoryType::LinearBlockAllocator] += blockSize * blockCount;
                m_MemoryUsages[usage] += blockSize * blockCount;
            }
            
            return LinearBlockAllocator(blockSize, blockCount, [usage, blockSize, blockCount]()
            {
                std::lock_guard lock(m_Mutex);
                m_MemoryTypes[MemoryType::LinearBlockAllocator] -= blockSize * blockCount;
                m_MemoryUsages[usage] -= blockSize * blockCount;
            });
        }

    private:
        static std::unordered_map<MemoryUsage, size_t> m_MemoryUsages;
        static std::unordered_map<MemoryType, size_t> m_MemoryTypes;
        static std::mutex m_Mutex;
    };

    template <typename T>
    using Vector = std::vector<T, Memory::TrackingAllocator<T>>;
}
