
#include "Vec.hpp"

namespace mrg
{
    template<class T>
    Vec3<T>::Vec3()  { m_x = 0; m_y = 0; m_z = 0; }

    template <class T>
    Vec3<T>::Vec3(std::initializer_list<T> l)
    {
        assert(l.size() >= 3);
        auto begin = l.begin();
        m_x = *(begin++);
        m_y = *(begin++);
        m_z = *(begin);
    }

    template<class T>
    T& Vec3<T>::X() { return m_x; }

    template<class T>
    T& Vec3<T>::Y() { return m_y; }

    template<class T>
    T& Vec3<T>::Z() { return m_z; }

    template<class T>
    T Vec3<T>::X() const { return m_x; }

    template<class T>
    T Vec3<T>::Y() const { return m_y; }

    template<class T>
    T Vec3<T>::Z() const { return m_z; }

    template<class T>
    Vec3<T>& Vec3<T>::operator=(const T value)
    {
        this->m_x = value;
        this->m_y = value;
        this->m_z = value;
        return *this;
    }

    template<class T>
    T& Vec3<T>::operator[](const unsigned int index)
    {
        assert(index <= 2);

        switch(index)
        {
            case 0 : return m_x;
            case 1 : return m_y;
            default : return m_z;
        }
    }

    template<class T>
    Vec3<T> Vec3<T>::operator+(const Vec3<T>& vec)
    {
        Vec3<T> result;
        result.m_x = vec.m_x + m_x;
        result.m_y = vec.m_y + m_y;
        result.m_z = vec.m_z + m_z;
        return result;
    }

    template<class T>
    Vec3<T> Vec3<T>::operator-(const Vec3<T>& vec)
    {
        Vec3<T> result;
        result.m_x = vec.m_x - m_x;
        result.m_y = vec.m_y - m_y;
        result.m_z = vec.m_z - m_z;
        return result;
    }

    template<class T>
    Vec3<T> Vec3<T>::operator*(const Vec3<T>& vec)
    {
        Vec3<T> result;
        result.m_x = vec.m_x * m_x;
        result.m_y = vec.m_y * m_y;
        result.m_z = vec.m_z * m_z;
        return result;
    }

    template<class T>
    Vec3<T> Vec3<T>::operator*(const T value)
    {
        Vec3<T> result;
        result.m_x = value * m_x;
        result.m_y = value * m_y;
        result.m_z = value * m_z;
        return result;
    }

    template<class T>
    Vec3<T> Vec3<T>::operator/(const T value)
    {
        assert(value != 0);

        Vec3<T> result;
        result.m_x = m_x / value;
        result.m_y = m_y / value;
        result.m_z = m_z / value;
        return result;
    }

    template<class T>
    Vec3<T>& Vec3<T>::operator+=(const Vec3<T> &vec)
    {
        this->m_x += vec.m_x;
        this->m_y += vec.m_y;
        this->m_z += vec.m_z;
        return *this;
    }

    template<class T>
    Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& vec)
    {
        this->m_x -= vec.m_x;
        this->m_y -= vec.m_y;
        this->m_z -= vec.m_z;
        return *this;
    }

    template<class T>
    Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& vec)
    {
        this->m_x *= vec.m_x;
        this->m_y *= vec.m_y;
        this->m_z *= vec.m_z;
        return *this;
    }

    template<class T>
    Vec3<T>& Vec3<T>::operator*=(const T value)
    {
        this->m_x *= value;
        this->m_y *= value;
        this->m_z *= value;
        return *this;
    }

    template<class T>
    double Vec3<T>::Length()
    {
        return mrg::Sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }

    template<class T>
    Vec3<T> Vec3<T>::Normalize() const
    {
        Vec3<T> result;
        double length = Length();

        result.m_x = m_x / length;
        result.m_y = m_y / length;
        result.m_z = m_z / length;

        return result;
    }

    template<class T>
    T& Vec3<T>::Get(const unsigned int index)
    {
        assert(index < 3);
        switch(index)
        {
            case 0 : return m_x;
            case 1 : return m_y;
            default : return m_z;
        }
    }

    template<class T>
    Vec4<T>::Vec4() : m_x(0), m_y(0), m_z(0), m_a(0) { }

    template<class T>
    Vec4<T>::Vec4(std::initializer_list<T> l)
    {
        assert(l.size() >= 4);
        auto begin = l.begin();
        m_x = *(begin++);
        m_y = *(begin++);
        m_z = *(begin++);
        m_a = *(begin);
    }

    template<class T>
    T& Vec4<T>::X(){ return m_x; }

    template<class T>
    T& Vec4<T>::Y(){ return m_y; }

    template<class T>
    T& Vec4<T>::Z(){ return m_z; }

    template<class T>
    T& Vec4<T>::A(){ return m_a; }

    template<class T>
    T& Vec4<T>::operator[](const unsigned int index)
    {
        assert(index <= 3);
        switch(index)
        {
            case 0 : return m_x;
            case 1 : return m_y;
            case 2 : return m_z;
            default : return m_a;
        }
    }

    template<class T>
    Vec4<T>& Vec4<T>::operator=(const T value)
    {
        m_x = value;
        m_y = value;
        m_z = value;
        m_a = value;
        return *this;
    }

    template<class T>
    Vec4<T> Vec4<T>::operator+(const Vec4<T>& vec)
    {
        Vec4<T> result;
        result.m_x = vec.m_x + m_x;
        result.m_y = vec.m_y + m_y;
        result.m_z = vec.m_z + m_z;
        result.m_a = vec.m_a + m_a;
        return result;
    }

    template<class T>
    Vec4<T> Vec4<T>::operator-(const Vec4<T>& vec)
    {
        Vec4<T> result;
        result.m_x = m_x - vec.m_x;
        result.m_y = m_y - vec.m_y;
        result.m_z = m_z - vec.m_z;
        result.m_a = m_a - vec.m_a;
        return result;
    }

    template<class T>
    Vec4<T> Vec4<T>::operator+(const T t)
    {
        Vec4<T> result;
        result.m_x = t + m_x;
        result.m_y = t + m_y;
        result.m_z = t + m_z;
        result.m_a = t + m_a;
        return result;
    }

    template<class T>
    Vec4<T> Vec4<T>::operator-(const T t)
    {
        Vec4<T> result;
        result.m_x = m_x - t;
        result.m_y = m_y - t;
        result.m_z = m_z - t;
        result.m_a = m_a - t;
        return result;
    }

    template<class T>
    Vec4<T> Vec4<T>::operator*(const Vec4<T>& vec)
    {
        Vec4<T> result;
        result.m_x = vec.m_x * m_x;
        result.m_y = vec.m_y * m_y;
        result.m_z = vec.m_z * m_z;
        result.m_a = vec.m_a * m_a;
        return result;
    }

    template<class T>
    Vec4<T> Vec4<T>::operator*(const T t)
    {
        Vec4<T> result;
        result.m_x = t * m_x;
        result.m_y = t * m_y;
        result.m_z = t * m_z;
        result.m_a = t * m_a;
        return result;
    }

    template<class T>
    Vec4<T> Vec4<T>::operator/(const T t)
    {
        Vec4<T> result;
        result.m_x = m_x / t;
        result.m_y = m_y / t;
        result.m_z = m_z / t;
        result.m_a = m_a / t;
        return result;
    }

    template<class T>
    Vec4<T>& Vec4<T>::operator+=(Vec4<T> const &vec)
    {
        m_x += vec.m_x;
        m_y += vec.m_y;
        m_z += vec.m_z;
        m_a += vec.m_a;
        return *this;
    }

    template<class T>
    Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& vec)
    {
        m_x -= vec.m_x;
        m_y -= vec.m_y;
        m_z -= vec.m_z;
        m_a -= vec.m_a;
        return *this;
    }

    template<class T>
    Vec4<T>& Vec4<T>::operator*=(const Vec4<T>& vec)
    {
        m_x *= vec.m_x;
        m_y *= vec.m_y;
        m_z *= vec.m_z;
        m_a *= vec.m_a;
        return *this;
    }

    template<class T>
    Vec4<T>& Vec4<T>::operator*=(const T value)
    {
        m_x *= value;
        m_y *= value;
        m_z *= value;
        m_a *= value;
        return *this;
    }

    template<class T>
    Vec4<T> Vec4<T>::Normalize() const
    {
        Vec4<T> result;
        double length = Length();

        result.m_x = m_x / length;
        result.m_y = m_y / length;
        result.m_z = m_z / length;
        result.m_a = m_a / length;

        return result;
    }

    template<class T>
    T& Vec4<T>::Get(const unsigned int index)
    {
        assert(index < 3);
        switch(index)
        {
            case 0 : return m_x;
            case 1 : return m_y;
            case 2 : return m_z;
            case 3 : return m_a;
            default : return 0;
        }
    }

    template<class T>
    double Vec4<T>::Length() const
    {
        return mrg::Sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_a * m_a);
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>::Vec(const Type initialise)
    {
        for(size_t i = 0; i < Size; i++)
            elements[i] = initialise;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>::Vec(const Vec<Type, Size>& vec)
    {
        elements = vec.elements;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>::Vec(std::initializer_list<Type> l)
    {
        assert(l.size() >= Size);

        auto element = l.begin();

        for (unsigned int i = 0; i < l.size(); ++i, ++element)
            elements[i] = *element;
    }

    template<class Type, unsigned int Size>
    Type Vec<Type, Size>::operator[](const unsigned int index) const
    {
        assert(index < Size);
        return elements[index];
    }

    template<class Type, unsigned int Size>
    Type& Vec<Type, Size>::operator[](const unsigned int index)
    {
        assert(index < Size);
        return elements[index];
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator=(const Type& value)
    {
        for(unsigned i = 0; i < Size; i++)
        {
            elements[i] = value;
        }
        return *this;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator*=(const Vec<Type, Size>& vec)
    {
        for(unsigned int i = 0; i < Size; i++)
        {
            elements[i] *= vec.elements[i];
        }
        return *this;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator*=(const Type t)
    {
        for(unsigned int i = 0; i < Size; i++)
        {
            elements[i] *= t;
        }
        return *this;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator+=(const Vec<Type, Size>& vec)
    {
        for(unsigned int i = 0; i < Size; i++)
        {
            elements[i] += vec[i];
        }
        return *this;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator+=(const Type t)
    {
        for(unsigned int i = 0; i < Size; i++)
        {
            elements[i] += t;
        }
        return *this;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator-=(const Vec<Type, Size>& vec)
    {
        for(unsigned int i = 0; i < Size; i++)
        {
            elements[i] -= vec[i];
        }
        return *this;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator-=(const Type t)
    {
        for(unsigned int i = 0; i < Size; i++)
        {
            elements[i] -= t;
        }
        return *this;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::operator+(const Vec<Type, Size>& vec) const
    {
        Vec<Type, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = elements[i] + vec.elements[i];
        }
        return result;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::operator-(const Vec<Type, Size>& vec) const
    {
        Vec<Type, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = elements[i] - vec.elements[i];
        }
        return result;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::operator*(const Vec<Type, Size>& vec) const
    {
        Vec<Type, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = elements[i] * vec.elements[i];
        }
        return result;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::operator*(const Type t) const
    {
        Vec<Type, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = elements[i] * t;
        }
        return result;
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::operator/(const Type t) const
    {
        Vec<Type, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = elements[i] / t;
        }
        return result;
    }

    template<class Type, unsigned int Size>
    double Vec<Type, Size>::Length() const
    {
        Type result = Type();
        for(int i = 0; i < Size; i++)
        {
            result += elements[i] * elements[i];
        }
        return mrg::Sqrt(result);
    }

    template<class Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::Normalize() const
    {
        Vec<Type, Size> result;
        double length = Length();

        for(unsigned int i = 0; i < Size; i++)
        {
            result.elements[i] = elements[i] / length;
        }
        return result;
    }

    template<class Type, unsigned int Size>
    Type& Vec<Type, Size>::Get(const unsigned int index)
    {
        return elements[index];
    }

    template<class Type, unsigned int Size>
    Type& Vec<Type, Size>::Get(const unsigned int index) const
    {
        return elements[index];
    }
}