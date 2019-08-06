//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef IMPRO_MATRIX_HPP
#define IMPRO_MATRIX_HPP

#include <array>
#include <type_traits>

#include "../Core/Vec.hpp"

namespace mrg {
    template<typename Type>
    class Matrix
    {
    public:
        Matrix();
        Matrix(const uint32_t width, const uint32_t height, const uint8_t channelNumber);
        Matrix(Type fill, const uint32_t width, const uint32_t height, const uint8_t channelNumber);
        Matrix(std::vector<Type>& pixels, const uint32_t width, const uint32_t height, const uint8_t channelNumber);
        Matrix(std::initializer_list<Type> pixels, const uint32_t width, const uint32_t height, const uint8_t channelNumber);

        template<typename T>
        Matrix<T> ToGrayScale();

        template<typename T>
        Matrix<Type> Convolve(Matrix<T> kernel) const;
        Matrix<double> Sobel();

        template<typename T>
        Matrix<T> Threshold() const;

        Type& Get(unsigned int w, unsigned int h);
        std::vector<Type>& GetData();

        template<typename ReturnType>
        ReturnType* GetRawData();

        void Set(uint32_t w, uint32_t h, const Type& t);
        [[nodiscard]] uint32_t Width() const noexcept { return width; }
        [[nodiscard]] uint32_t Height() const noexcept { return height; }
        [[nodiscard]] uint8_t Channel() const noexcept { return channelNumber; }
    private:
        uint32_t width;
        uint32_t height;
        uint8_t channelNumber;
        std::vector<Type> data;
    };

    const Matrix<double> gaussianBlurKernel5x5 = Matrix<double>({1.0/256.0, 4.0/256.0,  6.0/256.0,  4.0/256.0,  1.0/256.0,
                                                                 4.0/256.0, 16.0/256.0, 24.0/256.0, 16.0/256.0, 4.0/256.0,
                                                                 6.0/256.0, 24.0/256.0, 36.0/256.0, 24.0/256.0, 6.0/256.0,
                                                                 4.0/256.0, 16.0/256.0, 24.0/256.0, 16.0/256.0, 4.0/256.0,
                                                                 1.0/256.0, 4.0/256.0,  6.0/256.0,  4.0/256.0,  1.0/256.0},
                                                                 5, 5, 1);

    const Matrix<double> gaussianBlurKernel3x3 = Matrix<double>({1.0/16.0, 2.0/16.0, 1.0/16.0,
                                                                 2.0/16.0, 4.0/16.0, 2.0/16.0,
                                                                 1.0/16.0, 2.0/16.0, 1.0/16.0},
                                                                3, 3, 1);

    const Matrix<double> sharpenKernel = Matrix<double>({0.0, -1.0, 0.0,
                                                         -1.0, 5.0, -1.0,
                                                         0.0, -1.0, 0.0},
                                                          3, 3, 1);

    const Matrix<double> boxBlurKernel = Matrix<double>({1.0/9.0, 1.0/9.0, 1.0/9.0,
                                                         1.0/9.0, 1.0/9.0, 1.0/9.0,
                                                         1.0/9.0, 1.0/9.0, 1.0/9.0},
                                                         3, 3, 1);


    const Matrix<double> unsharpKernel5x5 = Matrix<double>({ -1.0/256.0, -4.0/256.0,  -6.0/256.0,  -4.0/256.0,  -1.0/256.0,
                                                             -4.0/256.0, -16.0/256.0, -24.0/256.0, -16.0/256.0, -4.0/256.0,
                                                             -6.0/256.0, -24.0/256.0, 476.0/256.0, -24.0/256.0, -6.0/256.0,
                                                             -4.0/256.0, -16.0/256.0, -24.0/256.0, -16.0/256.0, -4.0/256.0,
                                                             -1.0/256.0, -4.0/256.0,  -6.0/256.0,  -4.0/256.0,  -1.0/256.0},
                                                                     5, 5, 1);

}

#include "Matrix.inl"

#endif //IMPRO_MATRIX_HPP