#include "PngParser.hpp"

#include <turbojpeg.h>
#include <iostream>
#include <fstream>

// With the help of : https://stackoverflow.com/questions/9094691/examples-or-tutorials-of-using-libjpeg-turbos-turbojpeg?lq=1

namespace mrg::ImageParser {

    template<typename T>
    Matrix<T> JpegParser<T>::Parse(std::string _fileName, const unsigned int channel)
    {

        long unsigned int _jpegSize = 0; //!< _jpegSize from above
        unsigned char *_compressedImage = nullptr; //!< _compressedImage from above
        int jpegSubsamp, width, height;

        tjhandle _jpegDecompressor = tjInitDecompress();

        tjDecompressHeader2(_jpegDecompressor, _compressedImage, _jpegSize, &width, &height, &jpegSubsamp);

        unsigned char buffer[width*height*channel]; //!< will contain the decompressed image

        tjDecompress2(_jpegDecompressor, _compressedImage, _jpegSize, buffer, width, 0/*pitch*/, height, TJPF_RGB, TJFLAG_FASTDCT);

        std::vector<T> resultData(width * height * channel);

        for(uint32_t j = 0; j < height; j++)
        {
            for(uint32_t i = 0; i < width; i++)
            {
                if constexpr (std::is_arithmetic<T>::value)
                {
                    for(uint32_t c = 0; c < channel; c++)
                    {
                        resultData.push_back(buffer[(j * width + i) * channel + c]);
                    }
                }
                else
                {
                    //buffer[(j * width + i) * channel + c] = resultData[i * height + j][c];
                }
            }
        }

        tjDestroy(_jpegDecompressor);

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
        }else if(nbands == 3){
            pixelFormat = TJPF_RGB;
            jpegSubsamp = TJSAMP_444;
        }else if(nbands == 4)
        {
            pixelFormat = TJPF_RGBA;
            jpegSubsamp = TJSAMP_444;
        }else
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
                        srcBuf[(j * width + i) * nbands + c] = data[j * width + i * nbands + c];
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
