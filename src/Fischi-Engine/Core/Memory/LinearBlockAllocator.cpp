#include "LinearBlockAllocator.h"

#include "Core/Log.h"

namespace FischiEngine
{
    void* LinearBlockAllocator::Allocate(size_t count)
    {
        std::lock_guard lock(m_Mutex);

        if (m_NextBlock + m_BlockSize * count > m_LastBlock)
        {
            Log::Warn("LinearBlockAllocator out of memory!");
            return nullptr;
        }
        
        void* result = m_NextBlock;
        m_NextBlock += m_BlockSize * count;
        return result;
    }

    void LinearBlockAllocator::Reset()
    {
        m_NextBlock = m_Memory;
    }

    void* LinearBlockAllocator::begin() const
    {
        return m_Memory;
    }

    void* LinearBlockAllocator::end() const
    {
        return m_NextBlock;
    }

    LinearBlockAllocator::LinearBlockAllocator(const size_t blockSize, const size_t blockCount, std::function<void()> deallocateCallback)
        : m_BlockSize(blockSize), m_BlockCount(blockCount), m_DeallocateCallback(deallocateCallback)
    {
        m_Memory = static_cast<char*>(malloc(blockSize * blockCount));
        m_NextBlock = m_Memory;
        m_LastBlock = m_Memory + blockSize * (blockCount - 1);
    }

    LinearBlockAllocator::~LinearBlockAllocator()
    {
        free(m_Memory);
        m_DeallocateCallback();
    }
}
