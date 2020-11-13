//
// Created by Platholl on 11/06/2020.
//

#include "catch.hpp"

#include "Mirage/Image/Matrix.hpp"

TEST_CASE( "Matrix", "[matrix]" )
{
    std::vector<char> pixels = {1 , 2 , 3,
                                4,  5 , 6,
                                7,  8,  9};
    const mrg::Matrix<char> mat {pixels, 3, 3, 1};

    SECTION("Generic tests")
    {
        REQUIRE(mat.Width()   == 3);
        REQUIRE(mat.Height()  == 3);
        REQUIRE(mat.Channel() == 1);

        uint8_t ite = 0;
        for(const auto& p : mat.Data())
            REQUIRE(p == pixels[ite++]);
    }

    SECTION("Pixel access")
    {
        REQUIRE(mat.Get({0, 0}, 0) == 1);
        REQUIRE(mat.Get({0, 1}, 0) == 2);
        REQUIRE(mat.Get({0, 2}, 0) == 3);
        REQUIRE(mat.Get({1, 0}, 0) == 4);
        REQUIRE(mat.Get({1, 1}, 0) == 5);
        REQUIRE(mat.Get({1, 2}, 0) == 6);
        REQUIRE(mat.Get({2, 0}, 0) == 7);
        REQUIRE(mat.Get({2, 1}, 0) == 8);
        REQUIRE(mat.Get({2, 2}, 0) == 9);
    }

    SECTION("Pixel modification")
    {
        mrg::Matrix<char> mat1 {pixels,3, 3, 1};

        mat1.Set({0, 0}, 0, -1);
        REQUIRE(mat1.Get({0, 0}, 0) == -1);
    }
}