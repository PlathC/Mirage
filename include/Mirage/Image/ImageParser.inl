#include <algorithm>
#include <functional>
#include <fstream>
#include <memory>

#include "Parser/IParser.hpp"
#include "Parser/PngParser.hpp"
#include "Parser/JpegParser.hpp"

namespace mrg
{
    namespace ImageParser
    {
        template<typename Type>
        Matrix<Type> FromFile(std::string fileName, const unsigned int channel) {
            std::unique_ptr<IParser<Type>> parser;
            Matrix<Type> result;

            if (!fs::exists(fileName.c_str()))
            {
                throw std::runtime_error("Can't find the image file.");
            }

            std::string::size_type idx = fileName.rfind('.');
            if (idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                auto CheckExtension = [&extension](ImageFile type) -> bool {
                    return std::find(formats.at(type).begin(),
                                     formats.at(type).end(), extension)
                           != formats.at(type).end();
                };

                if (CheckExtension(ImageFile::PNG))
                {
                    parser = std::make_unique<PngParser<Type>>();
                }
                else if (CheckExtension(ImageFile::JPEG))
                {
                    parser = std::make_unique<JpegParser<Type>>();
                }
                result = parser->Parse(fileName, channel);
            }

            return result;
        }


        template<typename Type>
        void ToFile(Matrix<Type> &mat, std::string fileName) {
            std::unique_ptr<IParser<Type>> parser;
            auto idx = fileName.rfind('.');

            if (idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                auto CheckExtension = [&extension](ImageFile type) -> bool
                {
                    return std::find(formats.at(type).begin(),
                                     formats.at(type).end(), extension)
                           != formats.at(type).end();
                };

                if (CheckExtension(ImageFile::PNG))
                {
                    parser = std::make_unique<PngParser<Type>>();
                }
                else if (CheckExtension(ImageFile::JPEG))
                {
                    parser = std::make_unique<JpegParser<Type>>();
                }

                if (parser)
                {
                    parser->Write(mat, fileName);
                }
            }

        }
    }
}