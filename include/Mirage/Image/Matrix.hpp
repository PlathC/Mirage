//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef MIRAGE_MATRIX_HPP
#define MIRAGE_MATRIX_HPP

#include <array>
#include <functional>
#include <type_traits>

#include "Mirage/Core/Vec.hpp"

namespace mrg
{
    template<class ImageType>
    class PixelArrayReference;

    template<class Type>
    class Matrix
    {
    public:
        Matrix();
        Matrix(uint32_t width, uint32_t height, uint8_t channelNumber = 1);
        Matrix(Type fill, uint32_t width, uint32_t height, uint8_t channelNumber = 1);
        Matrix(const std::vector<Type>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber = 1);

        template<std::size_t Size>
        Matrix(const std::array<Type, Size>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber = 1);
        Matrix(std::initializer_list<Type> pixels, uint32_t width, uint32_t height, uint8_t channelNumber = 1);

        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) noexcept = default;

        Matrix& operator=(const Matrix&) = default;
        Matrix& operator=(Matrix&&) noexcept = default;

        Matrix operator*(const Matrix& mask);
        Matrix operator*(Type scalar);
        Matrix& operator*=(const Matrix& mask);
        Matrix& operator*=(Type scalar);

        Matrix operator+(const Matrix& mask);
        Matrix operator+(Type scalar);
        Matrix& operator+=(const Matrix& mask);
        Matrix& operator+=(Type scalar);

        std::vector<Vec2<uint32_t>> operator>(Type scalar);
        std::vector<Vec2<uint32_t>> operator<(Type scalar);
        std::vector<Vec2<uint32_t>> operator>=(Type scalar);
        std::vector<Vec2<uint32_t>> operator<=(Type scalar);
        std::vector<Vec2<uint32_t>> operator!=(Type scalar);
        std::vector<Vec2<uint32_t>> operator==(Type scalar);

        PixelArrayReference<Type> operator[](const std::vector<Vec2<uint32_t>>& indices);
        PixelArrayReference<Type> operator()(const Vec2<uint32_t>& p1, const Vec2<uint32_t>& p2);

        Type& Get(uint32_t x, uint32_t y, uint8_t channel = 0);
        Type Get(uint32_t x, uint32_t y, uint8_t channel = 0) const;
        Type& Get(const Vec2<uint32_t>& position, uint8_t channel = 0);
        Type Get(const Vec2<uint32_t>& position, uint8_t channel = 0) const;
        Type& Get(const Vec3<uint32_t>& position);
        Type Get(const Vec3<uint32_t>& position) const;

        void Set(const Vec2<uint32_t>& position, uint8_t k, const Type& t);

        std::vector<Type>& Data();
        const std::vector<Type>& Data() const;

        [[nodiscard]] inline uint32_t Width() const noexcept { return m_width; }
        [[nodiscard]] inline uint32_t Height() const noexcept { return m_height; }
        [[nodiscard]] inline uint8_t Channel() const noexcept { return m_channelNumber; }

    private:
        uint32_t m_width;
        uint32_t m_height;
        uint8_t m_channelNumber;
        std::vector<Type> m_data;
    };

    template<class InputType, class ReturnType>
    Matrix<ReturnType> Transform(const Matrix<InputType>& img, std::function<ReturnType(const InputType&)> transformation);

    template<class ImageType>
    class PixelArrayReference
    {
    public:
        PixelArrayReference(const std::vector<std::reference_wrapper<ImageType>>& data);

        PixelArrayReference& operator*=(ImageType scalar);
        PixelArrayReference& operator/=(ImageType scalar);
        PixelArrayReference& operator+=(ImageType scalar);
        PixelArrayReference& operator-=(ImageType scalar);
        PixelArrayReference& operator=(ImageType scalar);
    private:
        std::vector<std::reference_wrapper<ImageType>> m_data;
    };
}

#include "Matrix.inl"

#endif //MIRAGE_MATRIX_HPP
