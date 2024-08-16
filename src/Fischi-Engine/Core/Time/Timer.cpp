#include "Timer.h"

namespace FischiEngine
{
    Timer::Timer()
    {
        Reset();
    }

    void Timer::Reset()
    {
        m_Start = std::chrono::high_resolution_clock::now();
    }

    float Timer::Elapsed() const
    {
        return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - m_Start).count());
    }

    float Timer::ElapsedMillis() const
    {
        return Elapsed() * 0.001f * 0.001f;
    }

    float Timer::ElapsedSeconds() const
    {
        return Elapsed() * 0.001f * 0.001f * 0.001f;
    }

    ScopedTimer::ScopedTimer(std::string name): m_Name(std::move(name))
    {
        
    }

    ScopedTimer::~ScopedTimer()
    {
        float time = m_Timer.ElapsedMillis();
        Log::Info("[TIMER] {0} - {1}ms", m_Name, time);
    }
}
