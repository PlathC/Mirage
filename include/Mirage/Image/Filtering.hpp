//
// Created by Cyprien Plateau--Holleville on 03/06/2020.
//

#ifndef MIRAGE_FILTERING_HPP
#define MIRAGE_FILTERING_HPP

#include <complex>
#include <map>

#include "Matrix.hpp"

namespace mrg
{
    template<class T>
    std::vector<std::size_t> ComputeHistogram(const std::vector<T> &channel);

    template<class T>
    std::vector<double> ComputeNormalizedHistogram(const std::vector<T> &channel);

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
    Matrix<ImageType> Convolve(const Matrix<ImageType>& img, const Matrix<KernelType>& kernel);

    template<class ImageType>
    using ConvolvingFunction = std::function<ImageType(const Matrix<ImageType>&)>;

    template<class ImageType>
    ImageType KernelMax(const Matrix<ImageType>& kernel);

    template<class ImageType>
    ImageType KernelMin(const Matrix<ImageType>& kernel);

    template <class ImageType>
    Matrix<ImageType> Convolve(Matrix<ImageType>& img, const ConvolvingFunction<ImageType>& convolvingFunction, uint32_t kernelSize);

    template<class ImageType>
    void Otsu(Matrix<ImageType>& img);

    template<class ImageType>
    void HistogramEqualization(Matrix<ImageType>& img);

    template<class ImageType>
    mrg::Matrix<std::complex<float>> DFT(const mrg::Matrix<ImageType>& img, bool inverse = false);

    static std::tuple<uint32_t, uint32_t> FindPaddingSize(uint32_t paddingSize);

    template<class ImageType>
    mrg::Matrix<ImageType> ZeroPadding(const mrg::Matrix<ImageType>& img, uint32_t newWidth, uint32_t newHeight);

    template<class ImageType>
    mrg::Matrix<ImageType> CropZeroPadding(const mrg::Matrix<ImageType>& img, uint32_t oldWidth, uint32_t oldHeight);

    template<class ImageType>
    mrg::Matrix<std::complex<float>> FFT2(const Matrix<ImageType>& img, bool inverse = false);

    template<class ImageType>
    std::vector<std::complex<float>> FFT(const std::vector<ImageType>& data, bool inverse = false);

    template<class ImageType>
    void FFTShift(Matrix<ImageType>& img);

    template<class ImageType>
    void IFFTShift(Matrix<ImageType>& img);

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

#include "Filtering.inl"

#endif //MIRAGE_FILTERING_HPP
