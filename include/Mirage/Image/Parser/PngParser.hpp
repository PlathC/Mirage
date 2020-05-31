//
// Created by Cyprien Plateau--Holleville on 22/06/2019.
//

#ifndef MIRAGE_PNGPARSER_HPP
#define MIRAGE_PNGPARSER_HPP

#include <png.h>
#include "IParser.hpp"

namespace mrg
{
    namespace ImageParser
    {
        template<typename T>
        class PngParser : public IParser<T> {
        public:
            Matrix<T> Parse(std::string _fileName, const unsigned int channel) override;

            void Write(Matrix<T> &mat, std::string _fileName) override;

        private:
            enum class ActionType {
                Read,
                Write
            };

            bool Init(ActionType actionType);

            std::string fileName;
            FILE *file = nullptr;

            png_byte colorType;
            png_byte bitDepth;
            png_structp png;
            png_infop info;
            png_bytep *rowPointers = nullptr;
        };
    }
}

#include "PngParser.inl"

#endif //MIRAGE_PNGPARSER_HPP
