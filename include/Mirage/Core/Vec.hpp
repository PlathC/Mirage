//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef MIRAGE_VEC_HPP
#define MIRAGE_VEC_HPP

#include <array>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>

#include "Mirage/Core/Math.hpp"

namespace mrg
{
    template<typename T>
    class Vec3 {
        static_assert(std::is_arithmetic<T>::value,
                      "The vector must store numbers");
    public:
        Vec3();
        Vec3(const Vec3& v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z) {}
        Vec3(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}
        Vec3(std::initializer_list<T> l);

        T& X();
        T& Y();
        T& Z();

        Vec3<T>& operator=(const T& value);
        Vec3<T>& operator=(const Vec3<T>& value);
        T& operator[](unsigned int index);
        Vec3<T> operator+(Vec3<T> const &vec);
        Vec3<T> operator*(Vec3<T> const &vec);
        Vec3<T> operator*(T value);
        Vec3<T>& operator+=(Vec3<T> const &vec);
        Vec3<T>& operator*=(Vec3<T> const &vec);

        double Length();
        T& Get(unsigned int index);

        friend std::ostream& operator<<(std::ostream& os, const Vec3<T>& v)
        {
            os << v.m_x << " " << v.m_y << " " << v.m_z;
            return os;
        }

    private:
        T m_x, m_y, m_z;
    };

    template<typename T>
    class Vec4 {
        static_assert(std::is_arithmetic<T>::value,
                      "The vector must store numbers");
    public:
        Vec4();
        Vec4(const Vec4& v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z), m_a(v.m_a){}
        explicit Vec4(T n) : m_x(n), m_y(n), m_z(n), m_a(n) {}
        Vec4(T x, T y , T z, T a) : m_x(x), m_y(y), m_z(z), m_a(a) { }
        Vec4(std::initializer_list<T> l);

        T& X();
        T& Y();
        T& Z();
        T& A();

        Vec4<T>& operator=(const T& value);
        Vec4<T>& operator=(const Vec4<T>& value);
        T& operator[](unsigned int index);
        Vec4<T> operator+(Vec4<T> const &vec);
        Vec4<T> operator+(T const &t);
        Vec4<T> operator*(T const &t);
        Vec4<T> operator*(Vec4<T> const &vec);
        Vec4<T> operator/(Vec4<T> const &vec);
        Vec4<T> operator/(T const &t);
        Vec4<T>& operator+=(Vec4<T> const &vec);
        Vec4<T>& operator*=(Vec4<T> const &vec);

        Vec4<T> Normalize() const;
        T& Get(unsigned int index);
        [[nodiscard]] double Length() const;

        friend std::ostream& operator<<(std::ostream& os, const Vec4<T>& v)
        {
            os << +v.m_x << " " << +v.m_y << " " << +v.m_z << " " << +v.m_a;
            return os;
        }

    private:
        T m_x, m_y, m_z, m_a;
    };


    template <typename Type, unsigned int Size>
    class Vec
    {
        static_assert(Size > 0, "The size must be > 0");
        static_assert(std::is_arithmetic<Type>::value,
                      "The vector must store numbers");

    public:
        Vec() = default;
        Vec(const Vec<Type, Size>& vec);
        explicit Vec(Type initialise);
        Vec(std::initializer_list<Type> l);

        Type& operator[](unsigned int index);
        Vec<Type, Size>& operator=(const Type& value);
        Vec<Type, Size>& operator*=(Vec<Type, Size> const &vec);
        Vec<Type, Size> operator+(Vec<Type, Size> const &vec);
        Vec<Type, Size> operator*(Vec<Type, Size> const &vec);

        [[nodiscard]] double Length() const;
        Vec<Type, Size> Normalize() const;
        Type& Get(unsigned int index);

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

    template<typename T>
    Vec3<T> Sqrt(Vec3<T> val)
    {
        return Vec3<T>(mrg::Sqrt(val.X()), mrg::Sqrt(val.Y()), mrg::Sqrt(val.Z()));
    }

    template<typename T>
    Vec4<T> Sqrt(Vec4<T> val)
    {
        return Vec4<T>(mrg::Sqrt(val.X()), mrg::Sqrt(val.Y()), mrg::Sqrt(val.Z()), mrg::Sqrt(val.A()));
    }

    template<typename T, unsigned int Size>
    Vec<T, Size> Sqrt(Vec<T, Size> val)
    {
        Vec<T, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = mrg::Sqrt(val[i]);
        }
        return result;
    }

    using Vec2c    = Vec<char, 2>;
    using Vec2i    = Vec<int, 2>;
    using Vec2ui8  = Vec<uint8_t, 2>;
    using Vec2ui16 = Vec<uint16_t, 2>;
    using Vec2ui32 = Vec<uint32_t, 2>;
    using Vec2f    = Vec<float, 2>;
    using Vec2l    = Vec<long, 2>;
    using Vec2d    = Vec<double, 2>;

    using Vec3c    = Vec3<char>;
    using Vec3i    = Vec3<int>;
    using Vec3ui8  = Vec3<uint8_t>;
    using Vec3ui16 = Vec3<uint16_t>;
    using Vec3ui32 = Vec3<uint32_t>;
    using Vec3f    = Vec3<float>;
    using Vec3l    = Vec3<long>;
    using Vec3d    = Vec3<double>;

    using Vec4c    = Vec4<char>;
    using Vec4i    = Vec4<int>;
    using Vec4ui8  = Vec4<uint8_t>;
    using Vec4ui16 = Vec4<uint16_t>;
    using Vec4ui32 = Vec4<uint32_t>;
    using Vec4f    = Vec4<float>;
    using Vec4l    = Vec4<long>;
    using Vec4d    = Vec4<double>;
}

#include "Vec.inl"

#endif //MIRAGE_VEC_HPP
