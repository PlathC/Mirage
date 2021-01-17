//
// Created by Cyprien Plateau--Holleville on 16/01/2021.
//

#include "catch.hpp"

#include <Mirage/Image/Filtering.hpp>

TEST_CASE("Padding", "[filtering]")
{
    std::vector<double> threeByThree = std::vector<double>(3 * 3, 1);
    const auto padded = mrg::ZeroPadding(mrg::Matrix<double>(threeByThree, 3, 3, 1), 8, 8);
    const auto newOriginal = mrg::CropZeroPadding(padded, 3, 3);

    REQUIRE(newOriginal.Width() == 3);
    REQUIRE(newOriginal.Height() == 3);

    for(uint32_t i = 0; i < 3; i++)
    {
        for(uint32_t j = 0; j < 3; j++)
        {
            REQUIRE(newOriginal.Get({i, j}, 0) == 1);
        }
    }
}

