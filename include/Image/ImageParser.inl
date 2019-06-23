#include <memory>
#include <algorithm>
#include <functional>

#include "Parser/IParser.h"
#include "Parser/PPMParser.h"
#include "Parser/PngParser.h"

namespace ImPro {
    namespace ImageParser{

        template<typename Type>
        Matrix<Type> FromFile(std::string fileName)
        {

            std::unique_ptr<IParser<Type>> parser;
            Matrix<Type> result;


            std::string::size_type idx = fileName.rfind('.');
            if(idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                auto CheckExtension = [&extension](ImageFile type) -> bool {
                    return std::find(formats.at(type).begin(),
                                     formats.at(type).end(), extension)
                                     != formats.at(type).end();
                };

                if(CheckExtension(ImageFile::PPM))
                {
                    parser = std::make_unique<PPMParser<Type>>();
                }else if(CheckExtension(ImageFile::PNG))
                {
                    parser = std::make_unique<PngParser<Type>>();
                }

                if(parser != nullptr)
                {
                    result = parser->Parse(fileName);
                }
            }

            return result;
        }


        template<typename Type>
        void ToFile(Matrix<Type>& mat, std::string fileName)
        {
            std::unique_ptr<IParser<Type>> parser;
            auto idx = fileName.rfind('.');
            if(idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
                auto CheckExtension = [&extension](ImageFile type) -> bool {
                    return std::find(formats.at(type).begin(),
                                     formats.at(type).end(), extension)
                           != formats.at(type).end();
                };

                if(CheckExtension(ImageFile::PPM))
                {
                    parser = std::make_unique<PPMParser<Type>>();
                }else if(CheckExtension(ImageFile::PNG))
                {
                    parser = std::make_unique<PngParser<Type>>();
                }

                if(parser != nullptr)
                {
                    parser->Write(mat, fileName);
                }
            }

        }
    }
}