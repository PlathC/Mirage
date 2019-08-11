#include <memory>
#include <algorithm>
#include <functional>
#include <fstream>

#include "Parser/IParser.hpp"
#include "Parser/PPMParser.hpp"
#include "Parser/PngParser.hpp"

namespace mrg {
    namespace ImageParser{

        template<typename Type>
        Matrix<Type> FromFile(std::string fileName, const unsigned int channel)
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

				std::ifstream f(fileName.c_str());

                bool exist = f.good();
                if(parser != nullptr && exist)
                {
                    result = parser->Parse(fileName, channel);
                }else if(!exist)
                {
                    throw std::runtime_error("Can't find the image file.");
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