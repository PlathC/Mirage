#include <memory>
#include <algorithm>

#include "Parser/IParser.h"
#include "Parser/PPMParser.h"

namespace ImPro {
    namespace ImageParser{

        template<typename Type>
        Matrix<Type> FromFile(std::string fileName)
        {
            //http://netpbm.sourceforge.net/doc/libppm.html
            std::unique_ptr<IParser<Type>> parser;
            Matrix<Type> result;

            int idx = fileName.rfind('.');
            if(idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                if(std::find(formats.at(ImageFile::PPM).begin(), formats.at(ImageFile::PPM).end(), extension)
                    != formats.at(ImageFile::PPM).end())
                {
                    parser = std::make_unique<PPMParser<Type>>();
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
            int idx = fileName.rfind('.');
            if(idx != std::string::npos)
            {
                std::string extension = fileName.substr(idx + 1);
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                if(std::find(formats.at(ImageFile::PPM).begin(), formats.at(ImageFile::PPM).end(), extension)
                   != formats.at(ImageFile::PPM).end())
                {
                    parser = std::make_unique<PPMParser<Type>>();
                }

                if(parser != nullptr)
                {
                    parser->Write(mat, fileName);
                }
            }

        }
    }
}