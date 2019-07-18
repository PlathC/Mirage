//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef IMPRO_MATH_HPP
#define IMPRO_MATH_HPP
#include <cmath>

namespace imp
{
    template<typename T>
    double Sqrt(T val)
    {
        return sqrt(static_cast<double>(val));
    }

    template<typename T>
    T Pow(T val, unsigned int power)
    {
        for(unsigned int i = 0; i < power; i++)
        {
            val *= val;
        }
        return val;
    }

    template<typename T>
    double Log(T val)
    {
        return log(val);
    }

    template<typename T>
    T Ceil(T n)
    {
        return std::ceil(n);
    }

    template<typename T>
    T Floor(T n)
    {
        return static_cast<T>(std::floor(n));
    }
}

#endif //IMPRO_MATH_HPP
