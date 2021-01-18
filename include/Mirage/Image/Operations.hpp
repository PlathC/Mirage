//
// Created by Cyprien Plateau--Holleville on 03/06/2020.
//

#ifndef MIRAGE_OPERATIONS_HPP
#define MIRAGE_OPERATIONS_HPP

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
    void Scale(Matrix<Type>& img, const uint32_t nWidth, const uint32_t nHeight, const ScalingFunction<Type> algorithm);

    template<class Type>
    Matrix<Type> Crop(const Matrix<Type>& img, const uint32_t bWidth, const uint32_t bHeight, const uint32_t eWidth, const uint32_t eHeight);

    template<class Type>
    Matrix<Type> Rotate(const Matrix<Type>& img, const double angle);
}

#include "Operations.inl"

#endif //MIRAGE_OPERATIONS_HPP
