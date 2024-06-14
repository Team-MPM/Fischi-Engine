#pragma once

#include <mutex>
#include <queue>
#include <vector>

#include "Event.h"

namespace FischiEngine
{
    class EventQueue
    {
    public:
        void Push(Event event)
        {
            std::lock_guard lock(m_Mutex);
        }

        std::vector<Event> PopAll()
        {
            std::lock_guard lock(m_Mutex);
            
        }

        bool Empty() const
        {
            std::lock_guard lock(m_Mutex);
        }

    private:
        mutable std::mutex m_Mutex;
    };
}
