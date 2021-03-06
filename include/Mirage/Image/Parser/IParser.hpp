//
// Created by Cyprien Plateau--Holleville on 22/06/2019.
//

#ifndef IMPRO_IPARSER_HPP
#define IMPRO_IPARSER_HPP

#include <string>
#include "../Matrix.hpp"

namespace mrg
{
    namespace ImageParser
    {
        template<typename T>
        class IParser {
        public:
            virtual Matrix <T> Parse(const std::string& fileName) = 0;

            virtual void Write(const Matrix <T> &mat, const std::string& fileName) = 0;

            virtual ~IParser() {};
        };
    }
}

#endif //IMPRO_IPARSER_HPP
