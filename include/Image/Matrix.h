//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef IMPRO_MATRIX_H
#define IMPRO_MATRIX_H

#include <array>
#include <type_traits>

#include "../Core/Vec.h"

namespace imp {
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
}

#include "Matrix.inl"

#endif //IMPRO_MATRIX_H
