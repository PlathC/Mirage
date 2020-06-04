//
// Created by Cyprien Plateau--Holleville on 29/08/2019.
//

#ifndef MIRAGE_JPEGPARSER_HPP
#define MIRAGE_JPEGPARSER_HPP

#include <fstream>
#include <iterator>

#include "IParser.hpp"

namespace mrg
{
    namespace ImageParser
    {
        template<typename T>
        class JpegParser : public IParser<T> {
        public:
            Matrix<T> Parse(const std::string& _fileName, const uint8_t channel) override;

            void Write(const Matrix<T>& mat, const std::string& _fileName) override;
        };
    }
}

#include "JpegParser.inl"

#endif //MIRAGE_JPEGPARSER_HPP
