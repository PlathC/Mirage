//
// Created by Cyprien Plateau--Holleville on 13/08/2019.
//

#ifndef MIRAGE_TIMER_HPP
#define MIRAGE_TIMER_HPP

#include <chrono>

namespace mrg
{
    class Timer
    {
    public:
        Timer();

        void Start();
        void Stop();
        double Duration() const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
        double m_duration;
    };
}


#endif //MIRAGE_TIMER_HPP
