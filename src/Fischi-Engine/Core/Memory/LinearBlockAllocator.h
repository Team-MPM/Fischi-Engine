#pragma once

#include <functional>
#include <mutex>

#include "Core/Core.h"

namespace FischiEngine
{
    class LinearBlockAllocator final
    {
    public:
        LinearBlockAllocator(size_t blockSize, size_t blockCount, std::function<void()> deallocateCallback);
        ~LinearBlockAllocator();
        void* Allocate(size_t count = 1);
        void Reset();

        void* begin() const;
        void* end() const;
    private:
        

        std::mutex m_Mutex;
        std::size_t m_BlockSize, m_BlockCount;
        char* m_Memory;
        char* m_NextBlock;
        char* m_LastBlock;
        std::function<void()> m_DeallocateCallback;
        
        friend class Memory;
    };
    
}
