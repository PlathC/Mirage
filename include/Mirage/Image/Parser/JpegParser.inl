#include "PngParser.hpp"

#include <turbojpeg.h>
#include <iostream>
#include <fstream>

// With the help of : https://stackoverflow.com/questions/9094691/examples-or-tutorials-of-using-libjpeg-turbos-turbojpeg?lq=1

namespace mrg
{
    namespace ImageParser
    {
        template<typename T>
        Matrix<T> JpegParser<T>::Parse(const std::string& _fileName)
        {
            std::ifstream file = std::ifstream(_fileName, std::ios::binary);

            file.ignore(std::numeric_limits<std::streamsize>::max());
            std::size_t fsize = static_cast<std::size_t>(file.gcount());

            file.clear();
            file.seekg( 0, std::ios_base::beg );

            std::vector<unsigned char> content = std::vector<unsigned char>(fsize + 1);

            while( file.read(reinterpret_cast<char*>(content.data()), static_cast<long long int>(content.size()))){}
            file.close();

            content[fsize] = 0;
            int jpegSubsamp = 0;
            int tempWidth = 0;
            int tempHeight = 0;
            int pixelFormat = TJPF_GRAY;

            tjhandle _jpegDecompressor = tjInitDecompress();
            if(tjDecompressHeader3(_jpegDecompressor,
                    content.data(), static_cast<long unsigned int>(fsize),
                    &tempWidth, &tempHeight, &jpegSubsamp, &pixelFormat) != 0)
            {
                tjDestroy(_jpegDecompressor);
                throw std::runtime_error("Error on decompressing header : " + std::string(tjGetErrorStr()));
            }

            uint8_t channel = 0;
            if(pixelFormat == TJPF_GRAY)
            {
                channel = 1;
            }
            else if(pixelFormat == TJPF_RGB || pixelFormat == TJPF_BGR)
            {
                channel = 3;
            }
            else if(pixelFormat == TJPF_RGBA)
            {
                channel = 4;
            }
            else
            {
                throw std::runtime_error("Unsupported format.");
            }

            uint32_t width = static_cast<uint32_t>(tempWidth);
            uint32_t height = static_cast<uint32_t>(tempHeight);

            std::vector<unsigned char> buffer = std::vector<unsigned char>(width * height * channel);
            if(tjDecompress2(_jpegDecompressor,
                    content.data(), static_cast<long unsigned int>(fsize), buffer.data(), tempWidth,
                    0, tempHeight, pixelFormat, TJFLAG_FASTDCT)
                    != 0)
            {
                tjDestroy(_jpegDecompressor);
                throw std::runtime_error("Error on decompressing image file : " + std::string(tjGetErrorStr()));
            }

            auto resultData = std::vector<T>(width * height * channel);
            std::transform(buffer.begin(), buffer.end(), resultData.begin(),
                           [](unsigned char x) { return static_cast<T>(x);});
            if(pixelFormat == TJPF_BGR)
            {
                for(uint32_t y = 0; y < height; y++)
                {
                    for(uint32_t x = 0; x < width; x++)
                    {
                        std::swap(resultData[(y * width * channel) + (x * channel)],
                                resultData[(y * width * channel) + (x * channel) + 2]);
                    }
                }
            }

            tjDestroy(_jpegDecompressor);
            return Matrix<T>(resultData, width, height, channel);
        }

        template<typename T>
        void JpegParser<T>::Write(const Matrix<T>& mat, const std::string& _fileName)
        {
            tjhandle handle = tjInitCompress();

            if(handle == nullptr)
            {
                throw std::runtime_error("Could not init libjpeg.");
            }

            int jpegQual = 98;
            uint32_t width = mat.Width();
            uint32_t height = mat.Height();
            uint8_t nbands = mat.Channel();
            int flags = 0;

            unsigned char* jpegBuf = nullptr;
            uint32_t pitch = width * nbands;
            int pixelFormat;
            int jpegSubsamp;
            if(nbands == 1)
            {
                pixelFormat = TJPF_GRAY;
                jpegSubsamp = TJSAMP_GRAY;
            }
            else if(nbands == 3)
            {
                pixelFormat = TJPF_RGB;
                jpegSubsamp = TJSAMP_444;
            }
            else if(nbands == 4)
            {
                pixelFormat = TJPF_RGBA;
                jpegSubsamp = TJSAMP_444;
            }
            else
            {
                throw std::runtime_error("Unsupported format.");
            }

            unsigned long jpegSize = 0;

            const std::vector<T>& data = mat.Data();
            auto srcBuf = std::vector<unsigned char>(width * height * nbands);
            std::transform(data.begin(), data.end(), srcBuf.begin(),
                           [](T x) { return static_cast<unsigned char>(x);});

            int tj_stat = tjCompress2(handle, srcBuf.data(), static_cast<int>(width), static_cast<int>(pitch),
                                      static_cast<int>(height), pixelFormat, &(jpegBuf), &jpegSize, jpegSubsamp,
                                      jpegQual, flags);
            if(tj_stat != 0)
            {
                const char *err = reinterpret_cast<const char *>(tjGetErrorStr());
                tjDestroy(handle);
                handle = nullptr;
                throw std::runtime_error("Libjpeg error" + std::string(err));
            }

            std::ofstream file = std::ofstream(_fileName, std::ios::binary | std::ios::trunc);

            try
            {
                file.write(reinterpret_cast<char*>(jpegBuf), static_cast<long int>(jpegSize));
            }
            catch(std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                throw e;
            }

            tjDestroy(handle); //should deallocate data buffer
        }
    }
}
