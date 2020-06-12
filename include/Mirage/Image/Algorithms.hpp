//
// Created by Platholl on 03/06/2020.
//

#ifndef MIRAGE_ALGORITHMS_HPP
#define MIRAGE_ALGORITHMS_HPP

#include <functional>

#include "Matrix.hpp"

namespace mrg
{

    struct ScalingSettings
    {
        uint32_t oldWidth;
        uint32_t oldHeight;
        uint32_t nWidth;
        uint32_t nHeight;
        uint8_t channelNumber;
        double xRatio;
        double yRatio;
    };

    template<class Type>
    using ScalingFunction = std::function<Type(uint32_t x, uint32_t y, uint8_t k,
                                               const std::vector<Type>& oldData, const ScalingSettings& settings)>;


    template<class Type>
    Type ScalingNearestNeighbor(uint32_t x, uint32_t y, uint8_t k,
                                const std::vector<Type>& oldData,
                                const ScalingSettings& settings);

    template<typename Type>
    void Scale(Matrix<Type>& img, uint32_t nWidth, uint32_t nHeight, ScalingFunction<Type> algorithm);

    template<typename Type>
    Matrix<Type> Crop(const Matrix<Type>& img, uint32_t bWidth, uint32_t bHeight, uint32_t eWidth, uint32_t eHeight);
}

#include "Algorithms.inl"

#endif //MIRAGE_ALGORITHMS_HPP
