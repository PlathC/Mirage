//
// Created by Cyprien Plateau--Holleville on 13/08/2019.
//

#include "Timer.hpp"

void Timer::Start()
{
    start = std::clock();
}

void Timer::Stop()
{
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}

double Timer::Duration()
{
    return duration;
}