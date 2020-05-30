
#include "Vec.hpp"

namespace mrg {
    template<typename T>
    Vec3<T>::Vec3()  { m_x = 0; m_y = 0; m_z = 0; }

    template <typename T>
    Vec3<T>::Vec3(std::initializer_list<T> l)
    {
        auto begin = l.begin();
        m_x = *(begin++);
        m_y = *(begin++);
        m_z = *(begin);
    }

    template<typename T>
    T& Vec3<T>::X() { return m_x; }

    template<typename T>
    T& Vec3<T>::Y() { return m_y; }

    template<typename T>
    T& Vec3<T>::Z() { return m_z; }

    template<typename T>
    Vec3<T>& Vec3<T>::operator=(const T& value)
    {
        this->m_x = value;
        this->m_y = value;
        this->m_z = value;
        return *this;
    }

    template<typename T>
    Vec3<T>& Vec3<T>::operator=(const Vec3<T>& value)
    {
        this->m_x = value.m_x;
        this->m_y = value.m_y;
        this->m_z = value.m_z;
        return *this;
    }

    template<typename T>
    T& Vec3<T>::operator[](const unsigned int index)
    {
        assert(index < 2);

        switch(index)
        {
            case 0 : return m_x;
            case 1 : return m_y;
            default : return m_z;
        }
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator+(Vec3<T> const &vec)
    {
        Vec3<T> result;
        result.m_x = vec.m_x + this->m_x;
        result.m_y = vec.m_y + this->m_y;
        result.m_z = vec.m_z + this->m_z;
        return result;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator*(Vec3<T> const &vec)
    {
        Vec3<T> result;
        result.m_x = vec.m_x * this->m_x;
        result.m_y = vec.m_y * this->m_y;
        result.m_z = vec.m_z * this->m_z;
        return result;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator*(T const value)
    {
        Vec3<T> result;
        result.m_x = value * this->m_x;
        result.m_y = value * this->m_y;
        result.m_z = value * this->m_z;
        return result;
    }

    template<typename T>
    Vec3<T>& Vec3<T>::operator+=(Vec3<T> const &vec)
    {
        this->m_x += vec.m_x;
        this->m_y += vec.m_y;
        this->m_z += vec.m_z;
        return *this;
    }

    template<typename T>
    Vec3<T>& Vec3<T>::operator*=(Vec3<T> const &vec)
    {
        this->m_x *= vec.m_x;
        this->m_y *= vec.m_y;
        this->m_z *= vec.m_z;
        return *this;
    }

    template<typename T>
    double Vec3<T>::Length()
    {
        return mrg::Sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }

    template<typename T>
    T& Vec3<T>::Get(unsigned int index)
    {
        assert(index < 3);
        switch(index)
        {
            case 0 : return m_x;
            case 1 : return m_y;
            default : return m_z;
        }
    }

    template<typename T>
    Vec4<T>::Vec4() : m_x(0), m_y(0), m_z(0), m_a(0) { }

    template<typename T>
    Vec4<T>::Vec4(std::initializer_list<T> l)
    {
        assert(l.size() >= 4);
        auto begin = l.begin();
        m_x = *(begin++);
        m_y = *(begin++);
        m_z = *(begin++);
        m_a = *(begin);
    }

    template<typename T>
    T& Vec4<T>::X(){ return m_x; }

    template<typename T>
    T& Vec4<T>::Y(){ return m_y; }

    template<typename T>
    T& Vec4<T>::Z(){ return m_z; }

    template<typename T>
    T& Vec4<T>::A(){ return m_a; }

    template<typename T>
    Vec4<T>& Vec4<T>::operator=(const T& value)
    {
        this->m_x = value;
        this->m_y = value;
        this->m_z = value;
        this->m_a = value;
        return *this;
    }

    template<typename T>
    Vec4<T>& Vec4<T>::operator=(const Vec4<T>& value)
    {
        this->m_x = value.m_x;
        this->m_y = value.m_y;
        this->m_z = value.m_z;
        this->m_a = value.m_a;
        return *this;
    }

    template<typename T>
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

    template<typename T>
    Vec4<T> Vec4<T>::operator+(T const &t)
    {
        Vec4<T> result;
        result.m_x = t + this->m_x;
        result.m_y = t + this->m_y;
        result.m_z = t + this->m_z;
        result.m_a = t + this->m_a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator+(Vec4<T> const &vec)
    {
        Vec4<T> result;
        result.m_x = vec.m_x + this->m_x;
        result.m_y = vec.m_y + this->m_y;
        result.m_z = vec.m_z + this->m_z;
        result.m_a = vec.m_a + this->m_a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator*(Vec4<T> const &vec)
    {
        Vec4<T> result;
        result.m_x = vec.m_x * this->m_x;
        result.m_y = vec.m_y * this->m_y;
        result.m_z = vec.m_z * this->m_z;
        result.m_a = vec.m_a * this->m_a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator*(T const &t)
    {
        Vec4<T> result;
        result.m_x = t * this->m_x;
        result.m_y = t * this->m_y;
        result.m_z = t * this->m_z;
        result.m_a = t * this->m_a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator/(Vec4<T> const &vec)
    {
        Vec4<T> result;
        result.m_x = vec.m_x / this->m_x;
        result.m_y = vec.m_y / this->m_y;
        result.m_z = vec.m_z / this->m_z;
        result.m_a = vec.m_a / this->m_a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator/(T const &t)
    {
        assert(m_x != 0);
        assert(m_y != 0);
        assert(m_z != 0);
        assert(m_a != 0);
        Vec4<T> result;
        result.m_x = t / this->m_x;
        result.m_y = t / this->m_y;
        result.m_z = t / this->m_z;
        result.m_a = t / this->m_a;
        return result;
    }

    template<typename T>
    Vec4<T>& Vec4<T>::operator+=(Vec4<T> const &vec)
    {
        this->m_x += vec.m_x;
        this->m_y += vec.m_y;
        this->m_z += vec.m_z;
        this->m_a += vec.m_a;
        return *this;
    }

    template<typename T>
    Vec4<T>& Vec4<T>::operator*=(Vec4<T> const &vec)
    {
        this->m_x *= vec.m_x;
        this->m_y *= vec.m_y;
        this->m_z *= vec.m_z;
        this->m_a *= vec.m_a;
        return *this;
    }

    template<typename T>
    Vec4<T> Vec4<T>::Normalize() const
    {
        Vec4<T> result;
        double length = this->Length();

        result.m_x = this->m_x / length;
        result.m_y = this->m_y / length;
        result.m_z = this->m_z / length;
        result.m_a = this->m_a / length;

        return result;
    }

    template<typename T>
    T& Vec4<T>::Get(unsigned int index)
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

    template<typename T>
    double Vec4<T>::Length() const
    {
        return mrg::Sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_a * m_a);
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size>::Vec(const Type initialise)
    {
        for(size_t i = 0; i < Size; i++)
            elements[i] = initialise;
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size>::Vec(const Vec<Type, Size>& vec)
    {
        this->elements = vec.elements;
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size>::Vec(std::initializer_list<Type> l)
    {
        auto element = l.begin();

        for (unsigned int i = 0; i < l.size(); ++i, ++element)
            elements[i] = *element;
    }

    template<typename Type, unsigned int Size>
    Type& Vec<Type, Size>::operator[](unsigned int index)
    {
        assert(index < Size);
        return elements[index];
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator=(const Type& value)
    {
        for(unsigned i = 0; i < Size; i++)
        {
            this->elements[i] = value;
        }
        return *this;
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size>& Vec<Type, Size>::operator*=(Vec<Type, Size> const &vec)
    {
        for(unsigned int i = 0; i < Size; i++)
        {
            this->elements[i] *= vec.elements[i];
        }
        return *this;
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::operator+(Vec<Type, Size> const &vec)
    {
        Vec<Type, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = this->elements[i] + vec.elements[i];
        }
        return result;
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::operator*(Vec<Type, Size> const &vec)
    {
        Vec<Type, Size> result;
        for(unsigned int i = 0; i < Size; i++)
        {
            result[i] = this->elements[i] * vec.elements[i];
        }
        return result;
    }

    template<typename Type, unsigned int Size>
    double Vec<Type, Size>::Length() const
    {
        Type result = Type();
        for(int i = 0; i < Size; i++)
        {
            result += this->elements[i] * this->elements[i];
        }
        return mrg::Sqrt(result);
    }

    template<typename Type, unsigned int Size>
    Vec<Type, Size> Vec<Type, Size>::Normalize() const
    {
        Vec<Type, Size> result;
        double length = this->Length();

        for(unsigned int i = 0; i < Size; i++)
        {
            result.elements[i] = this->elements[i] / length;
        }
        return result;
    }

    template<typename Type, unsigned int Size>
    Type& Vec<Type, Size>::Get(unsigned int index)
    {
        return this->elements[index];
    }
}