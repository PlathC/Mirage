
#include "Vec.hpp"

namespace mrg {
    template<typename T>
    Vec3<T>::Vec3()  { x = 0; y = 0; z = 0; }

    template <typename T>
    Vec3<T>::Vec3(std::initializer_list<T> l)
    {
        auto begin = l.begin();
        x = *(begin++);
        y = *(begin++);
        z = *(begin);
    }

    template<typename T>
    T& Vec3<T>::X() { return x; }

    template<typename T>
    T& Vec3<T>::Y() { return y; }

    template<typename T>
    T& Vec3<T>::Z() { return z; }

    template<typename T>
    Vec3<T>& Vec3<T>::operator=(const T& value)
    {
        this->x = value;
        this->y = value;
        this->z = value;
        return *this;
    }

    template<typename T>
    Vec3<T>& Vec3<T>::operator=(const Vec3<T>& value)
    {
        this->x = value.x;
        this->y = value.y;
        this->z = value.z;
        return *this;
    }

    template<typename T>
    T& Vec3<T>::operator[](const unsigned int index)
    {
        assert(index < 2);

        switch(index)
        {
            case 0 : return x;
            case 1 : return y;
            default : return z;
        }
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator+(Vec3<T> const &vec)
    {
        Vec3<T> result;
        result.x = vec.x + this->x;
        result.y = vec.y + this->y;
        result.z = vec.z + this->z;
        return result;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator*(Vec3<T> const &vec)
    {
        Vec3<T> result;
        result.x = vec.x * this->x;
        result.y = vec.y * this->y;
        result.z = vec.z * this->z;
        return result;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator*(T const value)
    {
        Vec3<T> result;
        result.x = value * this->x;
        result.y = value * this->y;
        result.z = value * this->z;
        return result;
    }

    template<typename T>
    Vec3<T>& Vec3<T>::operator+=(Vec3<T> const &vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        this->z += vec.z;
        return *this;
    }

    template<typename T>
    Vec3<T>& Vec3<T>::operator*=(Vec3<T> const &vec)
    {
        this->x *= vec.x;
        this->y *= vec.y;
        this->z *= vec.z;
        return *this;
    }

    template<typename T>
    double Vec3<T>::Length()
    {
        return mrg::Sqrt(x * x + y * y + z * z);
    }

    template<typename T>
    T& Vec3<T>::Get(unsigned int index)
    {
        assert(index < 3);
        switch(index)
        {
            case 0 : return x;
            case 1 : return y;
            default : return z;
        }
    }

    template<typename T>
    Vec4<T>::Vec4() : x(0), y(0), z(0), a(0) { }

    template<typename T>
    Vec4<T>::Vec4(std::initializer_list<T> l)
    {
        assert(l.size() >= 4);
        auto begin = l.begin();
        x = *(begin++);
        y = *(begin++);
        z = *(begin++);
        a = *(begin);
    }

    template<typename T>
    T& Vec4<T>::X(){ return x; }

    template<typename T>
    T& Vec4<T>::Y(){ return y; }

    template<typename T>
    T& Vec4<T>::Z(){ return z; }

    template<typename T>
    T& Vec4<T>::A(){ return a; }

    template<typename T>
    Vec4<T>& Vec4<T>::operator=(const T& value)
    {
        this->x = value;
        this->y = value;
        this->z = value;
        this->a = value;
        return *this;
    }

    template<typename T>
    Vec4<T>& Vec4<T>::operator=(const Vec4<T>& value)
    {
        this->x = value.x;
        this->y = value.y;
        this->z = value.z;
        this->a = value.a;
        return *this;
    }

    template<typename T>
    T& Vec4<T>::operator[](const unsigned int index)
    {
        assert(index <= 3);
        switch(index)
        {
            case 0 : return x;
            case 1 : return y;
            case 2 : return z;
            default : return a;
        }
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator+(T const &t)
    {
        Vec4<T> result;
        result.x = t + this->x;
        result.y = t + this->y;
        result.z = t + this->z;
        result.a = t + this->a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator+(Vec4<T> const &vec)
    {
        Vec4<T> result;
        result.x = vec.x + this->x;
        result.y = vec.y + this->y;
        result.z = vec.z + this->z;
        result.a = vec.a + this->a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator*(Vec4<T> const &vec)
    {
        Vec4<T> result;
        result.x = vec.x * this->x;
        result.y = vec.y * this->y;
        result.z = vec.z * this->z;
        result.a = vec.a * this->a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator*(T const &t)
    {
        Vec4<T> result;
        result.x = t * this->x;
        result.y = t * this->y;
        result.z = t * this->z;
        result.a = t * this->a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator/(Vec4<T> const &vec)
    {
        Vec4<T> result;
        result.x = vec.x / this->x;
        result.y = vec.y / this->y;
        result.z = vec.z / this->z;
        result.a = vec.a / this->a;
        return result;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator/(T const &t)
    {
        assert(x != 0);
        assert(y != 0);
        assert(z != 0);
        assert(a != 0);
        Vec4<T> result;
        result.x = t / this->x;
        result.y = t / this->y;
        result.z = t / this->z;
        result.a = t / this->a;
        return result;
    }

    template<typename T>
    Vec4<T>& Vec4<T>::operator+=(Vec4<T> const &vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        this->z += vec.z;
        this->a += vec.a;
        return *this;
    }

    template<typename T>
    Vec4<T>& Vec4<T>::operator*=(Vec4<T> const &vec)
    {
        this->x *= vec.x;
        this->y *= vec.y;
        this->z *= vec.z;
        this->a *= vec.a;
        return *this;
    }

    template<typename T>
    Vec4<T> Vec4<T>::Normalize() const
    {
        Vec4<T> result;
        double length = this->Length();

        result.x = this->x / length;
        result.y = this->y / length;
        result.z = this->z / length;
        result.a = this->a / length;

        return result;
    }

    template<typename T>
    T& Vec4<T>::Get(unsigned int index)
    {
        assert(index < 3);
        switch(index)
        {
            case 0 : return x;
            case 1 : return y;
            case 2 : return z;
            case 3 : return a;
            default : return 0;
        }
    }

    template<typename T>
    double Vec4<T>::Length() const
    {
        return mrg::Sqrt(x * x + y * y + z * z + a * a);
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