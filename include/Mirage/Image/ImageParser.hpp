//
// Created by Cyprien Plateau--Holleville on 20/06/2019.
//

#ifndef IMPRO_IMAGEPARSER_HPP
#define IMPRO_IMAGEPARSER_HPP

#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <any>
#include <utility>
#include <unordered_map>

#include "../Core/Vec.hpp"
#include "Matrix.hpp"

namespace mrg {
    namespace ImageParser {

        enum ImageFile {
            PPM,
            PNG
        };

        const std::unordered_map<ImageFile, std::vector<std::string>> formats = {
                {ImageFile::PPM, {"ppm", "pgm", "pmm", "pnm"}},
                {ImageFile::PNG, {"png"}}
        };

        template<typename Type>
        Matrix<Type> FromFile(std::string fileName, const unsigned int channel);

        template<typename Type>
        void ToFile(Matrix<Type>& mat, std::string fileName);

    };
}

#include "ImageParser.inl"

#endif //IMPRO_IMAGEPARSER_HPP
