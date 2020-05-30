//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef IMPRO_IMAGEPARSER_HPP
#define IMPRO_IMAGEPARSER_HPP

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

#include "../Core/Vec.hpp"
#include "Matrix.hpp"

namespace mrg::ImageParser {

        enum ImageFile
        {
            PPM,
            PNG,
            JPEG
        };

        const std::unordered_map<ImageFile, std::vector<std::string>> formats = {
                {ImageFile::PPM, {"ppm", "pgm", "pmm", "pnm"}},
                {ImageFile::PNG, {"png"}},
                {ImageFile::JPEG, {"jpeg", "jpg"}}
        };

        template<typename Type>
        Matrix<Type> FromFile(std::string fileName, unsigned int channel);

        template<typename Type>
        void ToFile(Matrix<Type>& mat, std::string fileName);

    }

#include "ImageParser.inl"

#endif //IMPRO_IMAGEPARSER_HPP
