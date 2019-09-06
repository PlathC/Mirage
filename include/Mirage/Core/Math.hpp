//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef IMPRO_MATH_HPP
#define IMPRO_MATH_HPP
#include <cmath>

namespace mrg
{
    constexpr double Pi = 3.14159265358979323846;

    double Atan(const double val)
    {
        return std::atan(val);
    }

    double Exp(const double val)
    {
        return std::exp(val);
    }

    double Sqrt(const double val)
    {
        return sqrt(val);
    }

    template<typename T>
    T Pow(const T val, const unsigned int power)
    {
        static_assert(std::is_arithmetic<T>::value, "This function only works with numbers.");
        return std::pow(val, power);
    }

    double Log(const double val)
    {
        return std::log(val);
    }

    double Sin(const double val)
    {
        return std::sin(val);
    }

    double Cos(const double val)
    {
        return std::cos(val);
    }

    template<typename T>
    T Ceil(const T n)
    {
        static_assert(std::is_arithmetic<T>::value, "This function only works with numbers.");
        return std::ceil(n);
    }

    template<typename T>
    T Floor(const T n)
    {
        static_assert(std::is_arithmetic<T>::value, "This function only works with numbers.");
        return static_cast<T>(std::floor(n));
    }
}

#endif //IMPRO_MATH_HPP
