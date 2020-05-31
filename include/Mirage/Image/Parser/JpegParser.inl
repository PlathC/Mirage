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
        Matrix<T> JpegParser<T>::Parse(std::string _fileName, const unsigned int channel)
        {
            FILE *f = fopen(_fileName.c_str(), "rb");
            fseek(f, 0, SEEK_END);
            long fsize = ftell(f);
            fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

            std::vector<unsigned char> content = std::vector<unsigned char>(fsize + 1);
            fread(content.data(), 1, fsize, f);
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

            if(tjDecompressHeader2(_jpegDecompressor, content.data(), fsize, &width, &height, &jpegSubsamp) != 0)
            {
                tjDestroy(_jpegDecompressor);
                throw std::runtime_error("Error on decompressing header");
            }

            std::vector<unsigned char> buffer = std::vector<unsigned char>(width * height * channel);
            if(tjDecompress2(_jpegDecompressor,
                    content.data(), fsize, buffer.data(), width,
                    0/*pitch*/, height, pixelFormat, TJFLAG_FASTDCT)
                    != 0)
            {
                tjDestroy(_jpegDecompressor);
                throw std::runtime_error("Error on decompressing image file.");
            }

            std::vector<T> resultData;
            resultData.resize(width * height * channel);
            for(uint32_t j = 0; j < static_cast<uint32_t>(height); j++)
            {
                for(uint32_t i = 0; i < static_cast<uint32_t>(width); i++)
                {
                    for(uint32_t c = 0; c < channel; c++)
                    {
                        resultData[(j * width + i) * channel + c] = buffer[(j * width + i) * channel + c];
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
            std::vector<unsigned char> srcBuf = std::vector<unsigned char>(width * height * nbands);
            for(uint32_t j = 0; j < height; j++)
            {
                for(uint32_t i = 0; i < width; i++)
                {
                    for(uint8_t c = 0; c < nbands; c++)
                    {
                        srcBuf[(j * width + i) * nbands + c] = data[(j * width + i) * nbands + c];
                    }
                }
            }

            int tj_stat = tjCompress2( handle, srcBuf.data(), width, pitch, height,
                    pixelFormat, &(jpegBuf), &jpegSize, jpegSubsamp, jpegQual, flags);
            if(tj_stat != 0)
            {
                const char *err = (const char *) tjGetErrorStr();
                tjDestroy(handle);
                handle = nullptr;
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
            tjDestroy(handle); //should deallocate data buffer
        }
    }
}
