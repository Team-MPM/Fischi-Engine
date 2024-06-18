#pragma once

#include <mutex>
#include <string.h>

#include "Event.h"
#include "Core/Memory/LinearBlockAllocator.h"

namespace FischiEngine
{
    class EventQueue
    {
    public:
        EventQueue();
        ~EventQueue();

        template <typename T>
        void PushEvent(const T& event)
        {
            static_assert(std::is_base_of_v<Event, T>, "T must inherit from Event");

            std::lock_guard lock(m_Mutex);
            void* newEvent = m_Allocator.Allocate();
            memcpy(newEvent, &event, sizeof(T));
        }

        void Clear();

        Event* begin() const;
        Event* end() const;

        static size_t GetMaxEventSize();
    private:
        LinearBlockAllocator m_Allocator;
        mutable std::mutex m_Mutex;
    };
}
