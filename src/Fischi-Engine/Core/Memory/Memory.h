#pragma once

#include <memory>
#include <unordered_map>

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
        Vector
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
        static constexpr Unique<T> CreateUnique(Args&&... args, MemoryUsage usage)
        {
            auto deleter = [usage](const T* ptr)
            {
                m_MemoryTypes[MemoryType::Unique] -= sizeof(T);
                m_MemoryUsages[usage] -= sizeof(T);
                delete ptr;
            };

            Unique<T> ptr(new T(std::forward<Args>(args)...), deleter);
            m_MemoryTypes[MemoryType::Unique] += sizeof(T);
            m_MemoryUsages[usage] += sizeof(T);

            return ptr;
        }

        template <typename T, typename... Args>
        static constexpr Shared<T> CreateShared(Args&&... args, MemoryUsage usage)
        {
            auto deleter = [usage](const T* ptr)
            {
                m_MemoryTypes[MemoryType::Shared] -= sizeof(T);
                m_MemoryUsages[usage] -= sizeof(T);
                delete ptr;
            };
            
            Shared<T> ptr(new T(std::forward<Args>(args)...), deleter);
            m_MemoryTypes[MemoryType::Shared] += sizeof(T);
            m_MemoryUsages[usage] += sizeof(T);

            return ptr;
        }

        template <typename T, typename... Args>
        static T* AllocateHeap(Args&&... args, const MemoryUsage usage)
        {
            T* ptr = new T(std::forward<Args>(args)...);
            m_MemoryTypes[MemoryType::Heap] += sizeof(T);
            m_MemoryUsages[usage] += sizeof(T);

            return ptr;
        }

        template <typename T>
        static void FreeHeap(T* ptr, const MemoryUsage usage)
        {
            m_MemoryTypes[MemoryType::Heap] -= sizeof(T);
            m_MemoryUsages[usage] -= sizeof(T);
            delete ptr;
        }

        template <typename T>
        class TrackingAllocator : public std::allocator<T>
        {
        public:
            MemoryUsage Usage;
            
            TrackingAllocator(MemoryUsage usage = MemoryUsage::Other) : Usage(usage) {}

            template <typename U>
            TrackingAllocator(const TrackingAllocator<U>& other) : Usage(other.Usage) {}

            
            template <typename U>
            struct rebind
            {
                typedef TrackingAllocator<U> other;
            };

            T* allocate(std::size_t n)
            {
                m_MemoryTypes[MemoryType::Vector] += sizeof(T);
                m_MemoryUsages[Usage] += sizeof(T);
                return std::allocator<T>::allocate(n);
            }

            void deallocate(T* p, std::size_t n)
            {
                m_MemoryTypes[MemoryType::Vector] -= sizeof(T);
                m_MemoryUsages[Usage] -= sizeof(T);
                std::allocator<T>::deallocate(p, n);
            }
        };

        template <typename T>
        using Vector = std::vector<T, Memory::TrackingAllocator<T>>;
        
        template <typename T>
        static Vector<T> NewVector(MemoryUsage usage, size_t capacity = 0)
        {
            std::vector<T, TrackingAllocator<T>> vec{TrackingAllocator<T> (usage)};
            vec.reserve(capacity);
            return vec;
        }

        static void LogMemoryUsage();

        static std::unordered_map<MemoryUsage, size_t> GetMemoryUsages() { return m_MemoryUsages; }
        static std::unordered_map<MemoryType, size_t> GetMemoryTypes() { return m_MemoryTypes; }
    private:
        static std::unordered_map<MemoryUsage, size_t> m_MemoryUsages;
        static std::unordered_map<MemoryType, size_t> m_MemoryTypes;
    };

    template <typename T>
    using Vector = std::vector<T, Memory::TrackingAllocator<T>>;
}
