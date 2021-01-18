//
// Created by Cyprien Plateau--Holleville on 11/06/2020.
//

#include "catch.hpp"

#include <filesystem>

namespace fs = std::filesystem;

#include "Mirage/Image/ImageParser.hpp"


TEST_CASE( "JPG", "[parser]" )
{
    mrg::Matrix<uint16_t> img;
    REQUIRE_NOTHROW(img = mrg::ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg"));

    CHECK(img.Width() == 1024);
    CHECK(img.Height() == 698);

    constexpr std::string_view testFolder = "./tests_output";

    if(!fs::exists(testFolder))
    {
        fs::create_directory(testFolder);
    }

    const std::string filePath = std::string(testFolder) + "/HouseDublin.jpg";
    REQUIRE_NOTHROW(mrg::ImageParser::ToFile<uint16_t>(img, filePath));
    CHECK(fs::exists(filePath));

    REQUIRE_NOTHROW(img = mrg::ImageParser::FromFile<uint16_t>(filePath));
    CHECK(img.Width() == 1024);
    CHECK(img.Height() == 698);

    fs::remove_all(testFolder);
}

TEST_CASE( "PNG", "[parser]" )
{
    mrg::Matrix<uint16_t> img;
    REQUIRE_NOTHROW(img = mrg::ImageParser::FromFile<uint16_t>("../samples/lena.png"));

    CHECK(img.Width()  == 220);
    CHECK(img.Height() == 220);

    constexpr std::string_view testFolder = "./tests_output";

    if(!fs::exists(testFolder))
    {
        fs::create_directory(testFolder);
    }

    const std::string filePath = std::string(testFolder) + "/lena.png";
    REQUIRE_NOTHROW(mrg::ImageParser::ToFile<uint16_t>(img, filePath));
    CHECK(fs::exists(filePath));

    REQUIRE_NOTHROW(img = mrg::ImageParser::FromFile<uint16_t>(filePath));
    CHECK(img.Width()  == 220);
    CHECK(img.Height() == 220);

    fs::remove_all(testFolder);
}