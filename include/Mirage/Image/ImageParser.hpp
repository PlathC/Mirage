//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef MIRAGE_IMAGEPARSER_HPP
#define MIRAGE_IMAGEPARSER_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

#include "Mirage/Core/Vec.hpp"
#include "Matrix.hpp"

namespace mrg
{
    namespace ImageParser
    {
        enum class ImageFile
        {
            PNG,
            JPEG
        };

        const std::unordered_map<ImageFile, std::vector<std::string>> formats = {
                {ImageFile::PNG, {"png"}},
                {ImageFile::JPEG, {"jpeg", "jpg"}}
        };

        template<typename Type>
        Matrix<Type> FromFile(const std::string& fileName);

        template<typename Type>
        void ToFile(const Matrix<Type>& mat, const std::string& fileName);
    }
}

#include "ImageParser.inl"

#endif //MIRAGE_IMAGEPARSER_HPP
