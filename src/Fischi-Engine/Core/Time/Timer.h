#pragma once

#include <chrono>

#include "Core/Log.h"

namespace FischiEngine
{
    class FISCHI_API Timer
    {
    public:
        explicit Timer();
        void Reset();

        float Elapsed() const;

        float ElapsedMillis() const;
        float ElapsedSeconds() const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };

    class FISCHI_API ScopedTimer
	{
	public:
		explicit ScopedTimer(std::string name);
		~ScopedTimer();

	private:
		std::string m_Name;
		Timer m_Timer;
	};
}
