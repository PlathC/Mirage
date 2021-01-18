#include <algorithm>
#include <locale>
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
        Matrix<Type> FromFile(const std::string& fileName)
        {
            static_assert(std::is_arithmetic<Type>::value, "Only arithmetic image can be loaded");
            std::unique_ptr<IParser<Type>> parser;
            Matrix<Type> result;

            if (!fs::exists(fileName.c_str()))
            {
                throw std::runtime_error("Can't find the image file " + fileName + " starting from "
                                        + fs::current_path().string());
            }

            std::string::size_type idx = fileName.rfind('.');
            if (idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(),
                               [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

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
                result = parser->Parse(fileName);
            }

            return result;
        }


        template<typename Type>
        void ToFile(const Matrix<Type>& mat, const std::string& fileName)
        {
            static_assert(std::is_arithmetic<Type>::value, "Only arithmetic image can be saved");
            std::unique_ptr<IParser<Type>> parser;
            auto idx = fileName.rfind('.');

            if (idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(), [](char c){
                    return static_cast<char>(std::tolower(c));
                });

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