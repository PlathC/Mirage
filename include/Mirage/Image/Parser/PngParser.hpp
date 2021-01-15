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
            Matrix<T> Parse(const std::string& fileName, uint8_t channel) override;

            void Write(const Matrix<T> &mat, const std::string& _fileName) override;

        private:
            enum class ActionType {
                Read,
                Write
            };

            //bool Init(ActionType actionType);

            png_byte m_colorType;
            png_byte m_bitDepth;

            //png_bytep* m_rowPointers = nullptr;
        };
    }
}

#include "PngParser.inl"

#endif //MIRAGE_PNGPARSER_HPP
