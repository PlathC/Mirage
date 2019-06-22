//
// Created by cypri on 22/06/2019.
//

#ifndef IMPRO_PPMPARSER_H
#define IMPRO_PPMPARSER_H

#include "IParser.h"
#include "../Matrix.h"

namespace ImPro {
    namespace ImageParser{
        template<typename T>
        class PPMParser : public IParser<T> {
            Matrix<T> Parse(std::string fileName) override;
            void Write(Matrix<T>& mat, std::string fileName) override;
        };
    }
}

#include "PPMParser.inl"

#endif //IMPRO_PPMPARSER_H
