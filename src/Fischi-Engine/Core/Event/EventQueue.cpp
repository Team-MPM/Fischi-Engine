#include "EventQueue.h"

#include "Core/Memory/Memory.h"
#include "EventDefs.h"

namespace FischiEngine
{
    template <typename T, typename... Ts>
    constexpr size_t MaxSize()
    {
        if constexpr (sizeof...(Ts) == 0)
        {
            return sizeof(T);
        }
        else
        {
            return sizeof(T) > MaxSize<Ts...>() ? sizeof(T) : MaxSize<Ts...>();
        }
    }

    size_t s_MaxEventSize = MaxSize<
        MouseMovedEvent,
        MouseScrolledEvent,
        MouseButtonPressedEvent,
        MouseButtonReleasedEvent,
        KeyPressedEvent,
        KeyReleasedEvent,
        WindowCloseEvent,
        WindowResizeEvent>();

    EventQueue::EventQueue()
        : m_Allocator(Memory::CreateLinearBlockAllocator(s_MaxEventSize, 10000, MemoryUsage::Application))
    {
    }

    EventQueue::~EventQueue()
    {
        m_Allocator.Reset();
    }

    void EventQueue::Clear()
    {
        m_Allocator.Reset();
    }

    Event* EventQueue::begin() const
    {
        return static_cast<Event*>(m_Allocator.begin());
    }

    Event* EventQueue::end() const
    {
        return static_cast<Event*>(m_Allocator.end());
    }

    size_t EventQueue::GetMaxEventSize()
    {
        return s_MaxEventSize;
    }
}
