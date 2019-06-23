//
// Created by Cyprien Plateau--Holleville on 22/06/2019.
//

#ifndef IMPRO_PNGPARSER_H
#define IMPRO_PNGPARSER_H

#include <png.h>
#include "IParser.h"

namespace ImPro {
    namespace ImageParser {

        template<typename T>
        class PngParser : public IParser<T> {
            Matrix<T> Parse(std::string fileName) override;
            void Write(Matrix<T>& mat, std::string fileName) override;
        };
    }
}

#include "PngParser.inl"

#endif //IMPRO_PNGPARSER_H
