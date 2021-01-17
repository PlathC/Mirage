//
// Created by Cyprien Plateau--Holleville on 12/06/2020.
//

#include "catch.hpp"

#include "Mirage/Image/Operations.hpp"

TEST_CASE("Scale", "[algorithm]")
{
    const std::vector<char> pixels = {1 , 2 , 3,
                                      4,  5 , 6,
                                      7,  8,  9};
    constexpr uint32_t fWidth = 3;
    constexpr uint32_t fHeight = 3;
    mrg::Matrix<char> mat = mrg::Matrix<char>(pixels, 3, 3, 1);

    mrg::Scale(mat, mat.Width() * 2, mat.Height() * 2,
               static_cast<mrg::ScalingFunction<char>>(&mrg::ScalingNearestNeighbor<char>));

    REQUIRE(mat.Width()  == fWidth  * 2);
    REQUIRE(mat.Height() == fHeight * 2);
    auto& d = mat.Data();
    for(uint32_t i = 0; i < mat.Width(); ++i)
    {
        for(uint32_t j = 0; j < mat.Height(); ++j)
        {
            const auto oldIndex = static_cast<std::size_t>(mrg::Floor(i / 2.) * fHeight
                                                           + mrg::Floor(j / 2.));
            REQUIRE(d[(i * mat.Height() + j)] == pixels[oldIndex]);
        }
    }
}

TEST_CASE("Crop", "[algorithm]")
{
    const std::vector<char> pixels = {1, 2,  3,  4,
                                      5, 6,  7,  8,
                                      9, 10, 11, 12};
    mrg::Matrix<char> mat = mrg::Matrix<char>(pixels, 3, 4, 1);

    mrg::Crop(mat, 1, 1, 3, 3);
    REQUIRE(mat.Width()         == 2);
    REQUIRE(mat.Height()        == 2);
    REQUIRE(mat.Data().size()   == 4);
    REQUIRE(mat.Get({0, 0}, 0)  == 6);
}

TEST_CASE("Rotate", "[algorithm]")
{
    const std::vector<char> pixels = {1, 2,  3,
                                      4, 5,  6,
                                      7, 8, 9};
    mrg::Matrix<char> mat = mrg::Matrix<char>(pixels, 3, 3, 1);

    mat = mrg::Rotate(mat, mrg::Pi/2);
    REQUIRE(mat.Get({0, 0}, 0) == 6);
}