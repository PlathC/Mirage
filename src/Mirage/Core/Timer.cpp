//
// Created by Cyprien Plateau--Holleville on 13/08/2019.
//

#include "Timer.hpp"

namespace mrg {

    Timer::Timer() :
            m_start(),
            m_duration(0.)
    {

    }

    void Timer::Start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    void Timer::Stop()
    {
        m_duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                std::chrono::high_resolution_clock::now() - m_start
                ).count();
    }

    double Timer::Duration() const
    {
        return m_duration;
    }
    
}