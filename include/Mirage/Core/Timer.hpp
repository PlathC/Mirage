//
// Created by Cyprien Plateau--Holleville on 13/08/2019.
//

#ifndef MIRAGE_TIMER_HPP
#define MIRAGE_TIMER_HPP

#include <ctime>
namespace mrg {
    class Timer
    {
    public:
        void Start();
        void Stop();
        double Duration();

    private:
        std::clock_t start;
        double duration;
    };

}


#endif //MIRAGE_TIMER_HPP
