//
// Created by Cyprien Plateau--Holleville on 11/06/2020.
//

#include "catch.hpp"

#include "Mirage/Image/Matrix.hpp"

TEST_CASE( "Matrix", "[matrix]" )
{
    std::vector<char> pixels = {1 , 2 , 3,
                                4,  5 , 6,
                                7,  8,  9};
    const mrg::Matrix<char> mat {pixels, 3, 3};

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
        mrg::Matrix<char> mat1 {pixels,3, 3};

        mat1.Set({0, 0}, 0, -1);
        REQUIRE(mat1.Get({0, 0}, 0) == -1);
    }

    SECTION("Masks multiplication")
    {
        mrg::Matrix<char> mat1 {pixels,3, 3};

        mat1 *= 2;
        const auto& data = mat1.Data();
        for(uint32_t i = 0; i < data.size(); i++)
        {
            REQUIRE(data[i] == pixels[i] * 2);
        }

        mat1 = mat1 * 2;
        for(uint32_t i = 0; i < data.size(); i++)
        {
            REQUIRE(data[i] == pixels[i] * 4);
        }

        mrg::Matrix<char> mask1 {{0, 0, 0, 0, 0, 0}, 2, 3};
        mat1 = mat1 * mask1;
        for(uint32_t i = 0; i < mat1.Width(); i++)
        {
            for(uint32_t j = 0; j < mat1.Height(); j++)
            {
                if(i < mask1.Width() && j < mask1.Height())
                    REQUIRE(mat1.Get({i, j}) == 0);
                else
                    REQUIRE(pixels[i * mat1.Height() + j] * 2);
            }
        }

        mrg::Matrix<char> mask2 {{0, 0, 0, 0, 0, 0, 0, 0, 0}, 3, 3};
        mat1 *= mask2;
        for(uint32_t i = 0; i < mat1.Width(); i++)
        {
            for(uint32_t j = 0; j < mat1.Height(); j++)
            {
                REQUIRE(mat1.Get({i, j}) == 0);
            }
        }
    }


    SECTION("Masks addition")
    {
        mrg::Matrix<char> mat1 {pixels,3, 3};

        mat1 += -1;
        const auto& data = mat1.Data();
        for(uint32_t i = 0; i < data.size(); i++)
        {
            REQUIRE(data[i] == pixels[i] - 1);
        }

        mat1 = mat1 + 2;
        for(uint32_t i = 0; i < data.size(); i++)
        {
            REQUIRE(data[i] == pixels[i] + 1);
        }

        mrg::Matrix<char> mask1 {{1, 1, 1, 1, 1, 1}, 2, 3};
        mat1 = mat1 + mask1;
        for(uint32_t i = 0; i < mat1.Width(); i++)
        {
            for(uint32_t j = 0; j < mat1.Height(); j++)
            {
                if(i < mask1.Width() && j < mask1.Height())
                    REQUIRE(data[(i * mat1.Height()) + j] == pixels[(i * mat1.Height()) + j] + 2);
                else
                    REQUIRE(data[(i * mat1.Height()) + j] == pixels[(i * mat1.Height()) + j] + 1);
            }
        }

        mrg::Matrix<char> mask2 {{1, 1, 1, 1, 1, 1, 1, 1, 1}, 3, 3};
        mat1 += mask2;
        for(uint32_t i = 0; i < mat1.Width(); i++)
        {
            for(uint32_t j = 0; j < mat1.Height(); j++)
            {
                if(i < mask1.Width() && j < mask1.Height())
                    REQUIRE(data[(i * mat1.Height()) + j] == pixels[(i * mat1.Height()) + j] + 3);
                else
                    REQUIRE(data[(i * mat1.Height()) + j] == pixels[(i * mat1.Height()) + j] + 2);
            }
        }
    }

    SECTION("Vector operations")
    {
        mrg::Matrix<char> mat1 {pixels,3, 3};

        mat1[mat1 == 2] = 3;
        REQUIRE(mat.Get({0, 1}) == 2);

        // Check = operator
        mrg::Matrix<char> mat2{{1, 0, 0, 0, 0, 0, 0, 0, 0}, 3, 3};
        mat2[mat2 == 0] = 2;
        REQUIRE(mat.Get({0, 0}) == 1);

        const auto& data = mat2.Data();
        for(std::size_t i = 1; i < data.size(); i++)
            REQUIRE(data[i] == 2);

        // Check -= operator
        mat2[mat2 >= 2] -= 2;
        REQUIRE(mat.Get({0, 0}) == 1);
        for(std::size_t i = 1; i < data.size(); i++)
            REQUIRE(data[i] == 0);

        // Check -= operator
        mat2[mat2 < 1] += 1;
        for(char i : data)
            REQUIRE(i == 1);

        // Check *= operator
        mat2[mat2 == 1] *= 2;
        for(char i : data)
            REQUIRE(i == 2);

        // Check *= operator
        mat2[mat2 == 2] /= 2;
        for(char i : data)
            REQUIRE(i == 1);
    }
}