//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef MIRAGE_MATH_HPP
#define MIRAGE_MATH_HPP

#include <bitset>
#include <deque>
#include <cassert>
#include <cmath>

namespace mrg
{
    constexpr double Pi  = 3.14159265358979323846;
    constexpr double Tau = 6.28318530717958647692;

    inline double Atan(const double val)
    {
        return std::atan(val);
    }

    inline double Exp(const double val)
    {
        return std::exp(val);
    }

    inline double Sqrt(const double val)
    {
        return std::sqrt(val);
    }

    template<typename T>
    T Pow(const T val, const unsigned int power)
    {
        static_assert(std::is_arithmetic<T>::value, "This function only works with numbers.");
        return std::pow(val, power);
    }

    inline double Log(const double val)
    {
        return std::log(val);
    }

    inline double Sin(const double val)
    {
        return std::sin(val);
    }

    inline double Cos(const double val)
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

    template<typename T>
    T Trunc(const T n)
    {
        static_assert(std::is_arithmetic<T>::value, "This function only works with numbers.");
        return static_cast<T>(std::trunc(n));
    }

    // From https://stackoverflow.com/a/600306
    inline bool IsPowerOf2(uint32_t x)
    {
        return std::bitset<32>(x).count() == 1;
    }

    inline uint8_t FindPowerOf2(uint32_t x)
    {
        auto bits = std::bitset<32>(x);
        uint8_t powerOf2 = 0;
        for(std::size_t i = 0; i < bits.size(); i++)
        {
            if(bits[i] == 1)
            {
                powerOf2 = static_cast<uint8_t>(i);
                break;
            }
        }

        return powerOf2;
    }

    constexpr inline uint32_t FindNextHighestPowerOf2(uint32_t x)
    {
        assert(x > 0 && "Input value should higher than 0.");
        x--;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        x++;
        return x;
    }

    // From https://stackoverflow.com/a/48557165
    template<std::size_t N>
    void BitsetReverse(std::bitset<N> &b)
    {
        for(std::size_t i = 0; i < N/2; ++i)
        {
            bool t = b[i];
            b[i] = b[N-i-1];
            b[N-i-1] = t;
        }
    }

    inline void BitsetReverse(std::deque<bool> &b)
    {
        for(std::size_t i = 0; i < b.size()/2; ++i)
        {
            bool t = b[i];
            b[i] = b[b.size()-i-1];
            b[b.size()-i-1] = t;
        }
    }
}

#endif //MIRAGE_MATH_HPP
