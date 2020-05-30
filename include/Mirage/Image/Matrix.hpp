//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef MIRAGE_MATRIX_HPP
#define MIRAGE_MATRIX_HPP

#include <array>
#include <map>
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
        Matrix();
        Matrix(uint32_t width, uint32_t height, uint8_t channelNumber);
        Matrix(Type fill, uint32_t width, uint32_t height, uint8_t channelNumber);
        Matrix(std::vector<Type>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber);

        template<std::size_t Size>
        Matrix(const std::array<Type, Size>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber);

        Matrix(std::initializer_list<Type> pixels, uint32_t width, uint32_t height, uint8_t channelNumber);

        template<typename T>
        Matrix<T> ToGrayScale();

        Matrix<double> Sobel();
        Matrix<double> Canny();

        template<typename T>
        Matrix<Type> Convolve(Matrix<T> kernel);

        template<typename T>
        Matrix<T> Threshold() const;

        Matrix<Type> HistogramEqualization();

        [[nodiscard]] Type Get(unsigned int w, unsigned int h) const;
        std::vector<Type>& GetData();

        template<class ReturnType>
        std::vector<ReturnType> GetRawData() const;

        void Set(uint32_t w, uint32_t h, const Type& t);
        [[nodiscard]] uint32_t Width() const noexcept { return m_width; }
        [[nodiscard]] uint32_t Height() const noexcept { return m_height; }
        [[nodiscard]] uint8_t Channel() const noexcept { return m_channelNumber; }
    private:
        uint32_t m_width;
        uint32_t m_height;
        uint8_t m_channelNumber;
        std::vector<Type> m_data;
    };

    template<int kernelSize>
    static Matrix<double> GenerateGaussianKernel(int sigma);

    template<typename T>
    static std::map<T, int> ComputeHistogram(const std::vector<T> &channel);
    template<typename T>
    static std::map<T, double> ComputeNormalizeHistogram(const std::vector<T> &channel, uint32_t width, uint32_t height);

    template<std::size_t size>
    constexpr std::array<double, size> AverageKernelGenerator = [] { // OR: constexpr auto table
        std::array<double, size> A = {};
        for (size_t i = 0; i < size; i++) {
            A[i] = 1.0 / static_cast<double>(size);
        }
        return A;
    }();

    const static Matrix<double> averageKernel5x5 = Matrix<double>(AverageKernelGenerator<25>,5, 5, 1);

    const static Matrix<double> gaussianBlurKernel5x5 = Matrix<double>({1.0/256.0, 4.0/256.0,  6.0/256.0,  4.0/256.0,  1.0/256.0,
                                                                        4.0/256.0, 16.0/256.0, 24.0/256.0, 16.0/256.0, 4.0/256.0,
                                                                        6.0/256.0, 24.0/256.0, 36.0/256.0, 24.0/256.0, 6.0/256.0,
                                                                        4.0/256.0, 16.0/256.0, 24.0/256.0, 16.0/256.0, 4.0/256.0,
                                                                        1.0/256.0, 4.0/256.0,  6.0/256.0,  4.0/256.0,  1.0/256.0},
                                                                       5, 5, 1);

    const static Matrix<double> gaussianBlurKernel3x3 = Matrix<double>({1.0/16.0, 2.0/16.0, 1.0/16.0,
                                                                        2.0/16.0, 4.0/16.0, 2.0/16.0,
                                                                        1.0/16.0, 2.0/16.0, 1.0/16.0},
                                                                       3, 3, 1);

    const static Matrix<double> sharpenKernel = Matrix<double>({0.0, -1.0, 0.0,
                                                                -1.0, 5.0, -1.0,
                                                                0.0, -1.0, 0.0},
                                                               3, 3, 1);

    const static Matrix<double> boxBlurKernel = Matrix<double>({1.0/9.0, 1.0/9.0, 1.0/9.0,
                                                                1.0/9.0, 1.0/9.0, 1.0/9.0,
                                                                1.0/9.0, 1.0/9.0, 1.0/9.0},
                                                               3, 3, 1);


    const static Matrix<double> unsharpKernel5x5 = Matrix<double>({ -1.0/256.0, -4.0/256.0,  -6.0/256.0,  -4.0/256.0,  -1.0/256.0,
                                                                    -4.0/256.0, -16.0/256.0, -24.0/256.0, -16.0/256.0, -4.0/256.0,
                                                                    -6.0/256.0, -24.0/256.0, 476.0/256.0, -24.0/256.0, -6.0/256.0,
                                                                    -4.0/256.0, -16.0/256.0, -24.0/256.0, -16.0/256.0, -4.0/256.0,
                                                                    -1.0/256.0, -4.0/256.0,  -6.0/256.0,  -4.0/256.0,  -1.0/256.0},
                                                                  5, 5, 1);
}

#include "Matrix.inl"

#endif //MIRAGE_MATRIX_HPP
