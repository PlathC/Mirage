//
// Created by Cyprien Plateau--Holleville on 22/06/2019.
//

#ifndef IMPRO_PNGPARSER_H
#define IMPRO_PNGPARSER_H

#include <png.h>
#include "IParser.h"

namespace imp {
    namespace ImageParser {

        template<typename T>
        class PngParser : public IParser<T> {
        public:
            Matrix<T> Parse(std::string fileName, const unsigned int channel) override;
            void Write(Matrix<T>& mat, std::string fileName) override;
        };
    }
}

#include "PngParser.inl"

#endif //IMPRO_PNGPARSER_H
