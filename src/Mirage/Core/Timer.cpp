//
// Created by Cyprien Plateau--Holleville on 13/08/2019.
//

#include "Timer.hpp"

namespace mrg {

    Timer::Timer() :
            m_start(0),
            m_duration(0)
    {

    }

    void Timer::Start()
    {
        m_start = std::clock();
    }

    void Timer::Stop()
    {
        m_duration = (static_cast<double>(std::clock()) - static_cast<double>(m_start))
                / static_cast<double>(CLOCKS_PER_SEC);
    }

    double Timer::Duration()
    {
        return m_duration;
    }
    
}