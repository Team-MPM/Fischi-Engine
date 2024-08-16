#include "Memory.h"

#include "Core/Log.h"

namespace FischiEngine
{
    std::unordered_map<MemoryUsage, size_t> Memory::m_MemoryUsages = std::unordered_map<MemoryUsage, size_t>();
    std::unordered_map<MemoryType, size_t> Memory::m_MemoryTypes = std::unordered_map<MemoryType, size_t>();
    std::mutex Memory::m_Mutex = std::mutex();

    // void Memory::LogMemoryUsage()
    // {
    //     size_t totalUsageMemory = 0;
    //
    //     Log::Info("Memory Usage:");
    //     for (const auto& [usage, size] : m_MemoryUsages)
    //     {
    //         std::string usageStr;
    //         switch (usage)
    //         {
    //         case MemoryUsage::Application: usageStr = "Application"; break;
    //         case MemoryUsage::Project: usageStr = "Project"; break;
    //         case MemoryUsage::Scene: usageStr = "Scene"; break;
    //         case MemoryUsage::Window: usageStr = "Window"; break;
    //         case MemoryUsage::Renderer: usageStr = "Renderer"; break;
    //         case MemoryUsage::Game: usageStr = "Game"; break;
    //         case MemoryUsage::Other: usageStr = "Other"; break;
    //         }
    //         Log::Info("\t{0}: {1} bytes", usageStr, size);
    //         totalUsageMemory += size;
    //     }
    //
    //     size_t totalTypeMemory = 0;
    //     Log::Info("Memory Types:");
    //     for (const auto& [type, size] : m_MemoryTypes)
    //     {
    //         std::string typeStr;
    //         switch (type)
    //         {
    //         case MemoryType::Unique: typeStr = "Unique"; break;
    //         case MemoryType::Shared: typeStr = "Shared"; break;
    //         case MemoryType::Arena: typeStr = "Arena"; break;
    //         case MemoryType::Heap: typeStr = "Heap"; break;
    //         case MemoryType::Pool: typeStr = "Pool"; break;
    //         case MemoryType::Vector: typeStr = "Vector"; break;
    //         case MemoryType::LinearBlockAllocator: typeStr = "LinearBlockAllocator"; break;
    //         }
    //         Log::Info("\t{0}: {1} bytes", typeStr, size);
    //         totalTypeMemory += size;
    //     }
    //
    //     if (totalUsageMemory != totalTypeMemory)
    //         Log::Error("Memory usage and memory type usage do not match!");
    //     
    //     Log::Info("Total memory usage: {0} bytes", totalTypeMemory);
    //     Log::Info("");
    // }

    std::unordered_map<MemoryUsage, size_t> Memory::GetMemoryUsages()
    {
        return m_MemoryUsages;
    }

    std::unordered_map<MemoryType, size_t> Memory::GetMemoryTypes()
    {
        return m_MemoryTypes;
    }

    LinearBlockAllocator Memory::CreateLinearBlockAllocator(size_t blockSize, size_t blockCount, MemoryUsage usage)
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
}
