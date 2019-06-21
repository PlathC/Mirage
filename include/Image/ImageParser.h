//
// Created by cypri on 20/06/2019.
//

#ifndef IMPRO_IMAGEPARSER_H
#define IMPRO_IMAGEPARSER_H

#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <any>
#include <utility>

#include "../Core/Vec.h"
#include "Matrix.h"

namespace ImPro {
    namespace ImageParser {

        template<typename Type>
        Matrix<Type> FromPPM(std::string fileName);

        template<typename Type>
        bool ToPPM(const Matrix<Type>& mat);

    };
}

#include "ImageParser.inl"

#endif //IMPRO_IMAGEPARSER_H
