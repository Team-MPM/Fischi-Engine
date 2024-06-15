#pragma once

#include <chrono>

#include "Core/Log.h"

namespace FischiEngine
{
    class Timer
    {
    public:
        explicit Timer() { Reset(); }
        void Reset() { m_Start = std::chrono::high_resolution_clock::now(); }
        
        float Elapsed() const
        {
            return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - m_Start).count());
        }

        float ElapsedMillis() const { return Elapsed() * 0.001f * 0.001f; }
        float ElapsedSeconds() const { return Elapsed() * 0.001f * 0.001f * 0.001f; }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };

    class ScopedTimer
	{
	public:
		explicit ScopedTimer(std::string name)
			: m_Name(std::move(name)) {}
		~ScopedTimer()
		{
			float time = m_Timer.ElapsedMillis();
			Log::Info("[TIMER] {0} - {1}ms", m_Name, time);
		}
	private:
		std::string m_Name;
		Timer m_Timer;
	};
}
