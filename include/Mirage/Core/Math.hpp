//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef IMPRO_MATH_HPP
#define IMPRO_MATH_HPP
#include <cmath>

namespace mrg
{
    template<typename T>
    double Sqrt(const T val)
    {
        return sqrt(static_cast<double>(val));
    }

    template<typename T>
    T Pow(const T val, const unsigned int power)
    {
        for(unsigned int i = 0; i < power; i++)
        {
            val *= val;
        }
        return val;
    }

    template<typename T>
    double Log(const T val)
    {
        return log(val);
    }

    template<typename T>
    T Ceil(const T n)
    {
        return std::ceil(n);
    }

    template<typename T>
    T Floor(const T n)
    {
        return static_cast<T>(std::floor(n));
    }
}

#endif //IMPRO_MATH_HPP
