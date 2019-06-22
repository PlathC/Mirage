//
// Created by cypri on 22/06/2019.
//

#ifndef IMPRO_IPARSER_H
#define IMPRO_IPARSER_H

#include <string>
#include "Matrix.h"

namespace ImPro {
    namespace ImageParser {
        template<typename T>
        class IParser {
        public:
            virtual Matrix<T> Parse(std::string fileName) = 0;
            virtual void Write(Matrix<T>& mat, std::string fileName) = 0;
        };
    }
}


#endif //IMPRO_IPARSER_H
