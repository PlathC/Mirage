//
// Created by cypri on 20/06/2019.
//

#ifndef IMPRO_VEC_H
#define IMPRO_VEC_H

#include <array>
#include <vector>
#include <iostream>
#include <cassert>
#include <string>
#include <type_traits>
#include <fstream>

#include "Math.h"

namespace ImPro
{

    template<typename T>
    class Vec3 {
    public:
        Vec3();
        Vec3(T x, T y , T z);

        T& X();
        T& Y();
        T& Z();

        Vec3<T>& operator=(const T& value);
        Vec3<T>& operator=(const Vec3<T>& value);
        T& operator[](const unsigned int index);
        Vec3<T> operator+(Vec3<T> const &vec);
        Vec3<T> operator*(Vec3<T> const &vec);
        Vec3<T>& operator+=(Vec3<T> const &vec);
        Vec3<T>& operator*=(Vec3<T> const &vec);

        double Length();
        T Get(unsigned int index);

        friend std::ostream& operator<<(std::ostream& os, const Vec3<T>& v)
        {
            os << v.x << " " << v.y << " " << v.z;
            return os;
        }

    private:
        T x, y, z;
    };

    template<typename T>
    class Vec4 {
    public:
        Vec4();
        Vec4(T x, T y , T z, T a);

        T& X();
        T& Y();
        T& Z();
        T& A();

        Vec4<T>& operator=(const T& value);
        Vec4<T>& operator=(const Vec4<T>& value);
        T& operator[](const unsigned int index);
        Vec4<T> operator+(Vec4<T> const &vec);
        Vec4<T> operator*(Vec4<T> const &vec);
        Vec4<T>& operator+=(Vec4<T> const &vec);
        Vec4<T>& operator*=(Vec4<T> const &vec);

        Vec4<T> Normalize();
        T Get(unsigned int index);
        double Length();

        friend std::ostream& operator<<(std::ostream& os, const Vec4<T>& v)
        {
            os << v.x << " " << v.y << " " << v.z << " " << v.a;
            return os;
        }

    private:
        T x, y, z, a;
    };


    template <typename Type, unsigned int Size>
    class Vec
    {
        static_assert(Size > 0, "The size must be > 0");
        static_assert(std::is_same<Type, double>::value
                      || std::is_same<Type, float>::value
                      || std::is_same<Type, long>::value
                      || std::is_same<Type, long>::value
                      || std::is_same<Type, unsigned int>::value
                      || std::is_same<Type, int>::value
                      || std::is_same<Type, char>::value,
                      "The vector must contains numbers");

    public:
        Vec();
        explicit Vec(const Type initialise);
        Vec(const Vec<Type, Size>& vec);
        Vec(std::array<Type, Size> elements);

        Type& operator[](unsigned int index);
        Vec<Type, Size>& operator=(const Type& value);
        Vec<Type, Size>& operator*=(Vec<Type, Size> const &vec);
        Vec<Type, Size> operator+(Vec<Type, Size> const &vec);
        Vec<Type, Size> operator*(Vec<Type, Size> const &vec);

        double Length();
        Vec<Type, Size> Normalize();
        Type Get(unsigned int index);

        friend std::ostream& operator<<(std::ostream& os, const Vec<Type, Size>& v)
        {
            os << v.elements[0];
            for(unsigned int i = 1; i < Size; i++)
                os << " " << v.elements[i];

            return os;
        }

    private:
        std::array<Type, Size> elements{};
    };

    using Vec2c = Vec<char, 2>;
    using Vec2i = Vec<int, 2>;
    using Vec2f = Vec<float, 2>;
    using Vec2l = Vec<long, 2>;
    using Vec2d = Vec<double, 2>;

    using Vec3c = Vec3<char>;
    using Vec3i = Vec3<int>;
    using Vec3f = Vec3<float>;
    using Vec3l = Vec3<long>;
    using Vec3d = Vec3<double>;

    using Vec4c = Vec4<char>;
    using Vec4i = Vec4<int>;
    using Vec4f = Vec4<float>;
    using Vec4l = Vec4<long>;
    using Vec4d = Vec4<double>;
}

#include "Vec.inl"

#endif //IMPRO_VEC_H
