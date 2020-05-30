//
// Created by Cyprien Plateau--Holleville on 13/08/2019.
//

#include "Timer.hpp"

namespace mrg {

    Timer::Timer() :
        start(0),
        duration(0)
    {

    }

    void Timer::Start()
    {
        start = std::clock();
    }

    void Timer::Stop()
    {
        duration = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    }

    double Timer::Duration()
    {
        return duration;
    }
    
}