#include <algorithm>
#include <cstdio>
#include <cstdlib>

#include "PngParser.hpp"


namespace mrg
{
    namespace ImageParser
    {
        // Using https://gist.github.com/niw/5963798

        template<class T>
        Matrix<T> PngParser<T>::Parse(const std::string& fileName, const uint8_t channel)
        {
            std::ifstream inStream{fileName, std::ios::binary};

            png_structp pngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            if(!pngReadStruct)
            {
                throw std::runtime_error("Can't read image.");
            }

            png_infop pngInfo = png_create_info_struct(pngReadStruct);
            if(!pngInfo)
            {
                throw std::runtime_error("Can't read image information.");
            }

            png_set_read_fn(pngReadStruct, &inStream, [](png_structp pngReadStruct, png_bytep data, png_size_t length) {
                png_voidp fileDescriptor = png_get_io_ptr(pngReadStruct);
                static_cast<std::istream*>(fileDescriptor)->read(reinterpret_cast<char*>(data),
                        static_cast<std::streamsize>(length));
            });

            png_read_info(pngReadStruct, pngInfo);

            uint32_t width  = png_get_image_width(pngReadStruct, pngInfo);
            uint32_t height = png_get_image_height(pngReadStruct, pngInfo);
            m_colorType = png_get_color_type(pngReadStruct, pngInfo);
            m_bitDepth  = png_get_bit_depth(pngReadStruct, pngInfo);

            if(m_bitDepth == 16)
                png_set_strip_16(pngReadStruct);

            // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
            if(m_colorType == PNG_COLOR_TYPE_GRAY && m_bitDepth < 8)
                png_set_expand_gray_1_2_4_to_8(pngReadStruct);

            if(png_get_valid(pngReadStruct, pngInfo, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(pngReadStruct);

            png_set_scale_16(pngReadStruct);
            png_read_update_info(pngReadStruct, pngInfo);

            auto imageRowsPtr = std::vector<png_bytep>(height);
            auto imageData = std::vector<png_byte>(width * height * channel);

            std::size_t maxHit = 0;
            for(unsigned int y = 0; y < height; y++)
            {
                imageRowsPtr[y] = &imageData[y * width * channel];
                maxHit = std::max(maxHit, static_cast<std::size_t>(y * width * channel));
            }

            png_read_image(pngReadStruct, imageRowsPtr.data());
            png_read_end(pngReadStruct, pngInfo);
            png_destroy_read_struct(&pngReadStruct, nullptr, &pngInfo);

            auto convertedType = std::vector<T>(imageData.size());
            std::transform(imageData.begin(), imageData.end(), convertedType.begin(),
                    [](png_byte x) { return static_cast<T>(x);});
            return Matrix<T>(convertedType, width, height, channel);
        }

        template<class T>
        void PngParser<T>::Write(const Matrix<T>& mat, const std::string& fileName)
        {
            //m_fileName = _fileName;
            png_structp pngWriteStruct = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            if(!pngWriteStruct)
            {
                throw std::runtime_error("Can't create write structure.");
            }

            auto file = std::ofstream(fileName, std::ios::binary);

            png_set_write_fn(pngWriteStruct, &file, [] (png_structp pngWriteStruct, png_bytep data, png_size_t length) {
                png_voidp fileDescriptor = png_get_io_ptr(pngWriteStruct);
                static_cast<std::ostream*>(fileDescriptor)->write(reinterpret_cast<char*>(data),
                                                                  static_cast<std::streamsize>(length));
            }, nullptr);

            png_infop infoStruct = png_create_info_struct(pngWriteStruct);
            if(!infoStruct)
            {
                throw std::runtime_error("Can't create information structure.");
            }

            int colorType;
            switch(mat.Channel())
            {
                case 1:
                    colorType = PNG_COLOR_TYPE_GRAY;
                    break;
                case 3:
                    colorType = PNG_COLOR_TYPE_RGB;
                    break;
                case 4:
                    colorType = PNG_COLOR_TYPE_RGBA;
                    break;
                default:
                    throw std::runtime_error("Unknown color type.");
            }

            // Output is 8bit depth, RGBA format.
            png_set_IHDR(
                    pngWriteStruct,
                    infoStruct,
                    mat.Width(), mat.Height(),
                    8,
                    colorType,
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT
            );

            png_write_info(pngWriteStruct, infoStruct);

            auto imageData = mat.DataInType<png_byte>();
            for(std::size_t y = 0; y < mat.Height(); y++)
            {
                png_write_row(pngWriteStruct, &imageData[y * mat.Width() * mat.Channel()]);
            }

            png_write_end(pngWriteStruct, nullptr);
            png_destroy_write_struct(&pngWriteStruct, &infoStruct);
        }
    }
}