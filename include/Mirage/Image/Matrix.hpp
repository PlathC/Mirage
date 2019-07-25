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
        Matrix(const unsigned int width, const unsigned int height, const unsigned int channelNumber);
        Matrix(Type fill, const unsigned int width, const unsigned int height, const unsigned int channelNumber);
        Matrix(std::vector<Type> pixels, const unsigned int width, const unsigned int height, const unsigned int channelNumber);

        template<typename T>
        Matrix<T> ToGrayScale();

        template<typename T>
        Matrix<Type> Convolve(Matrix<T> kernel);
        Matrix<double> Sobel();

        template<typename T>
        Matrix<T> Threshold();

        Type& Get(unsigned int w, unsigned int h);
        std::vector<Type> GetData();
        void Set(unsigned int w, unsigned int h, const Type& t);
        unsigned int Width() noexcept { return width; }
        unsigned int Height() noexcept { return height; }

    private:
        unsigned int width;
        unsigned int height;
        unsigned int channelNumber;
        std::vector<Type> data;
    };

    const Matrix<double> gaussianBlurKernel5x5 = Matrix<double>(std::vector<double>({ 1.0/256.0, 4.0/256.0,  6.0/256.0,  4.0/256.0,  1.0/256.0,
                                                                                      4.0/256.0, 16.0/256.0, 24.0/256.0, 16.0/256.0, 4.0/256.0,
                                                                                      6.0/256.0, 24.0/256.0, 36.0/256.0, 24.0/256.0, 6.0/256.0,
                                                                                      4.0/256.0, 16.0/256.0, 24.0/256.0, 16.0/256.0, 4.0/256.0,
                                                                                      1.0/256.0, 4.0/256.0,  6.0/256.0,  4.0/256.0,  1.0/256.0}),
                                                                 5, 5, 1);

    const Matrix<double> gaussianBlurKernel3x3 = Matrix<double>(std::vector<double>({1.0/16.0, 2.0/16.0, 1.0/16.0,
                                                                                      2.0/16.0, 4.0/16.0, 2.0/16.0,
                                                                                      1.0/16.0, 2.0/16.0, 1.0/16.0}),
                                                                3, 3, 1);

    const Matrix<double> sharpenKernel = Matrix<double>(std::vector<double>({0.0, -1.0, 0.0,
                                                                                        -1.0, 5.0, -1.0,
                                                                                        0.0, -1.0, 0.0}),
                                                          3, 3, 1);

    const Matrix<double> boxBlurKernel = Matrix<double>(std::vector<double>({1.0/9.0, 1.0/9.0, 1.0/9.0,
                                                                             1.0/9.0, 1.0/9.0, 1.0/9.0,
                                                                             1.0/9.0, 1.0/9.0, 1.0/9.0}),
                                                        3, 3, 1);


    const Matrix<double> unsharpKernel5x5 = Matrix<double>(std::vector<double>({ -1.0/256.0, -4.0/256.0,  -6.0/256.0,  -4.0/256.0,  -1.0/256.0,
                                                                                      -4.0/256.0, -16.0/256.0, -24.0/256.0, -16.0/256.0, -4.0/256.0,
                                                                                      -6.0/256.0, -24.0/256.0, 476.0/256.0, -24.0/256.0, -6.0/256.0,
                                                                                      -4.0/256.0, -16.0/256.0, -24.0/256.0, -16.0/256.0, -4.0/256.0,
                                                                                      -1.0/256.0, -4.0/256.0,  -6.0/256.0,  -4.0/256.0,  -1.0/256.0}),
                                                                5, 5, 1);

}

#include "Matrix.inl"

#endif //IMPRO_MATRIX_HPP
