//
// Created by cypri on 20/06/2019.
//

#ifndef IMPRO_MATH_H
#define IMPRO_MATH_H
#include <cmath>

namespace ImPro
{
    template<typename T>
    double Sqrt(T val)
    {
        return sqrt(static_cast<double>(val));
    }

    template<typename T>
    T Pow(T val, int power)
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
}

#endif //IMPRO_MATH_H
