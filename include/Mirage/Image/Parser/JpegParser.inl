#include "PngParser.hpp"

#include <turbojpeg.h>
#include <iostream>
#include <fstream>

// With the help of : https://stackoverflow.com/questions/9094691/examples-or-tutorials-of-using-libjpeg-turbos-turbojpeg?lq=1

namespace mrg::ImageParser {

    template<typename T>
    Matrix<T> JpegParser<T>::Parse(std::string _fileName, const unsigned int channel)
    {
        FILE *f = fopen(_fileName.c_str(), "rb");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

        auto *content = new unsigned char[fsize + 1];
        fread(content, 1, fsize, f);
        fclose(f);

        content[fsize] = 0;
        int jpegSubsamp = 0, width = 0, height = 0;
        int pixelFormat;
        if(channel == 1)
        {
            pixelFormat = TJPF_GRAY;
        }
        else if(channel == 3)
        {
            pixelFormat = TJPF_RGB;
        }
        else if(channel == 4)
        {
            pixelFormat = TJPF_RGBA;
        }
        else
        {
            throw std::runtime_error("Unsupported format.");
        }

        tjhandle _jpegDecompressor = tjInitDecompress();

        if(tjDecompressHeader2(_jpegDecompressor, content, fsize, &width, &height, &jpegSubsamp) != 0)
        {
            delete[] content;
            tjDestroy(_jpegDecompressor);
            throw std::runtime_error("Error on decompressing header");
        }

        auto *buffer = new unsigned char[width * height * channel]; //!< will contain the decompressed image

        if(tjDecompress2(_jpegDecompressor,
                content, fsize, buffer, width,
                0/*pitch*/, height, pixelFormat, TJFLAG_FASTDCT)
                != 0)
        {
            tjDestroy(_jpegDecompressor);
            delete[] content;
            delete[] buffer;
            throw std::runtime_error("Error on decompressing image file.");
        }

        std::vector<T> resultData;
        resultData.resize(width * height);
        for(uint32_t j = 0; j < static_cast<uint32_t>(height); j++)
        {
            for(uint32_t i = 0; i < static_cast<uint32_t>(width); i++)
            {
                if constexpr (std::is_arithmetic<T>::value)
                {
                    for(uint32_t c = 0; c < channel; c++)
                    {
                        resultData[i * height + j * channel + c] = buffer[(j * width + i) * channel + c];
                    }
                }
                else
                {
                    T t = T();
                    for(uint32_t c = 0; c < channel; c++)
                        t[c] = buffer[(j * width + i) * channel + c];
                    resultData[i * height + j] = t;
                }
            }
        }

        tjDestroy(_jpegDecompressor);
        delete[] content;
        delete[] buffer;
        return Matrix<T>(resultData, width, height, channel);
    }

    template<typename T>
    void JpegParser<T>::Write(Matrix<T>& mat, std::string _fileName)
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

        std::vector<T> data = mat.GetData();
        auto* srcBuf = new unsigned char[width * height * nbands];
        for(uint32_t j = 0; j < height; j++)
        {
            for(uint32_t i = 0; i < width; i++)
            {
                for(uint8_t c = 0; c < nbands; c++)
                {
                    if constexpr (std::is_arithmetic<T>::value)
                    {
                        srcBuf[(j * width + i) * nbands + c] = data[i * height + j * nbands + c];
                    }
                    else
                    {
                        srcBuf[(j * width + i) * nbands + c] = data[i * height + j][c];
                    }
                }
            }
        }

        int tj_stat = tjCompress2( handle, srcBuf, width, pitch, height,
                                   pixelFormat, &(jpegBuf), &jpegSize, jpegSubsamp, jpegQual, flags);
        if(tj_stat != 0)
        {
            const char *err = (const char *) tjGetErrorStr();
            tjDestroy(handle);
            handle = nullptr;
            delete[] srcBuf;
            throw std::runtime_error("Libjpeg error" + std::string(err));
        }

        FILE *file = fopen(_fileName.c_str(), "wb");
        if (!file) {
            throw std::runtime_error("Could not open JPEG file");
        }

        if (fwrite(jpegBuf, jpegSize, 1, file) < 1) {
            throw std::runtime_error("Could not write JPEG file" );
        }

        fclose(file);
        delete[] srcBuf;
        tjDestroy(handle); //should deallocate data buffer
    }
}
