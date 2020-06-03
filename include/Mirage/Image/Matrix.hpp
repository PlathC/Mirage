//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef MIRAGE_MATRIX_HPP
#define MIRAGE_MATRIX_HPP

#include <array>
#include <type_traits>

#include "Mirage/Core/Vec.hpp"

namespace mrg
{
    template<typename Type>
    class Matrix
    {
    // TODO: add only arithmetic types ==> Add Get<T> method and store only has
    static_assert(std::is_arithmetic<Type>::value, "A matrix can only store arithmetic values.");
    public:

    public:
        Matrix();
        Matrix(uint32_t width, uint32_t height, uint8_t channelNumber);
        Matrix(Type fill, uint32_t width, uint32_t height, uint8_t channelNumber);
        Matrix(const std::vector<Type>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber);
        template<std::size_t Size>
        Matrix(const std::array<Type, Size>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber);
        Matrix(std::initializer_list<Type> pixels, uint32_t width, uint32_t height, uint8_t channelNumber);

        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) = default;

        Matrix& operator=(const Matrix&) = default;
        Matrix& operator=(Matrix&&) = default;

        [[nodiscard]] Type& Get(uint32_t w, uint32_t h, uint8_t channel);
        [[nodiscard]] Type Get(uint32_t w, uint32_t h, uint8_t channel) const;
        void Set(uint32_t w, uint32_t h, uint8_t k, const Type& t);

        std::vector<Type>& Data();
        const std::vector<Type>& Data() const;

        template<class ReturnType>
        std::vector<ReturnType> DataInType() const;

        [[nodiscard]] inline uint32_t Width() const noexcept { return m_width; }
        [[nodiscard]] inline uint32_t Height() const noexcept { return m_height; }
        [[nodiscard]] inline uint8_t Channel() const noexcept { return m_channelNumber; }

    private:
        uint32_t m_width;
        uint32_t m_height;
        uint8_t m_channelNumber;
        std::vector<Type> m_data;
    };
}

#include "Matrix.inl"

#endif //MIRAGE_MATRIX_HPP
