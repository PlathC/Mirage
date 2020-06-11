//
// Created by Platholl on 11/06/2020.
//

#include "catch.hpp"

#include "Mirage/Image/ImageParser.hpp"

TEST_CASE( "JPG", "[jpg]" )
{
    mrg::Matrix<uint16_t> img;
    REQUIRE_NOTHROW(img = mrg::ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg", 3));


    CHECK(img.Width() == 1024);
    CHECK(img.Height() == 698);
}

TEST_CASE( "PNG", "[png]" )
{
    mrg::Matrix<uint16_t> img;
    REQUIRE_NOTHROW(img = mrg::ImageParser::FromFile<uint16_t>("../samples/lena.png", 4));


    CHECK(img.Width()  == 220);
    CHECK(img.Height() == 220);
}