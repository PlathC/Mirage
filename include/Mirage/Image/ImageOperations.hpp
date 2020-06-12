//
// Created by Platholl on 03/06/2020.
//

#ifndef MIRAGE_IMAGEOPERATIONS_HPP
#define MIRAGE_IMAGEOPERATIONS_HPP

#include <map>

#include "Matrix.hpp"

namespace mrg
{
    template<class T>
    std::map<T, int> ComputeHistogram(const std::vector<T> &channel);

    template<class T>
    std::map<T, double> ComputeNormalizedHistogram(const std::vector<T> &channel, uint32_t width, uint32_t height);

    template<std::size_t size>
    constexpr std::array<double, size> AverageKernelGenerator = [] {
        std::array<double, size> A = {};
        for (size_t i = 0; i < size; i++) {
            A[i] = 1.0 / static_cast<double>(size);
        }
        return A;
    }();

    template<class ImageType, class ReturnType>
    Matrix<ReturnType> ToGrayScale(const Matrix<ImageType>& img);

    template<class Type>
    Matrix<double> Sobel(const Matrix<Type>& img);

    template<class Type>
    Matrix<double> Canny(const Matrix<Type>& img);

    template<class ImageType, class KernelType>
    void Convolve(Matrix<ImageType>& img, const Matrix<KernelType>& kernel);

    template<class ImageType>
    void Threshold(Matrix<ImageType>& img);

    template<class ImageType>
    void HistogramEqualization(Matrix<ImageType>& img);

    template<int kernelSize>
    Matrix<double> GenerateGaussianKernel(const int sigma);

    const Matrix<double> averageKernel5x5 = Matrix<double>(AverageKernelGenerator<25>,5, 5, 1);

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

#include "ImageOperations.inl"

#endif //MIRAGE_IMAGEOPERATIONS_HPP
