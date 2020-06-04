#include <cstdio>
#include <cstdlib>
#include "PngParser.hpp"


namespace mrg
{
    namespace ImageParser
    {
        // Using https://gist.github.com/niw/5963798

        template<class T>
        Matrix<T> PngParser<T>::Parse(const std::string& _fileName, const uint8_t channel)
        {
            m_fileName = _fileName;

            if(!Init(ActionType::Read))
                return Matrix<T>();

            png_read_info(m_png, m_info);

            unsigned int width, height;
            width     = png_get_image_width(m_png, m_info);
            height    = png_get_image_height(m_png, m_info);
            m_colorType = png_get_color_type(m_png, m_info);
            m_bitDepth  = png_get_bit_depth(m_png, m_info);

            if(m_bitDepth == 16)
                png_set_strip_16(m_png);

            // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
            if(m_colorType == PNG_COLOR_TYPE_GRAY && m_bitDepth < 8)
                png_set_expand_gray_1_2_4_to_8(m_png);

            if(png_get_valid(m_png, m_info, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(m_png);

            // These color_type don't have an alpha channel then fill it with 0xff.
            if(m_colorType == PNG_COLOR_TYPE_RGB ||
               m_colorType == PNG_COLOR_TYPE_GRAY ||
               m_colorType == PNG_COLOR_TYPE_PALETTE)
                png_set_filler(m_png, 0xFF, PNG_FILLER_AFTER);

            if(m_colorType == PNG_COLOR_TYPE_GRAY ||
               m_colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
                png_set_gray_to_rgb(m_png);

            png_read_update_info(m_png, m_info);

            m_rowPointers = new png_bytep[height];

            for(unsigned int y = 0; y < height; y++) {
                m_rowPointers[y] = new png_byte[png_get_rowbytes(m_png, m_info)];
            }

            png_read_image(m_png, m_rowPointers);
            fclose(m_file);
            png_destroy_read_struct(&m_png, &m_info, nullptr);

            std::vector<T> result(width * height * channel);

            for(unsigned int y = 0; y < height; y++)
            {
                png_bytep row = m_rowPointers[y];
                for(unsigned int x = 0; x < width; x++)
                {
                    png_bytep px = &(row[x * 4]);
                    for(unsigned int k = 0; k < channel; k++)
                    {
                        result[(y * width + x) * channel + k] = px[k];
                    }
                }
            }

            return Matrix<T>(result, width, height, channel);
        }

        template<class T>
        void PngParser<T>::Write(const Matrix<T>& mat, const std::string& _fileName)
        {
            m_fileName = _fileName;
            if(!Init(ActionType::Write))
                return;

            // Output is 8bit depth, RGBA format.
            png_set_IHDR(
                    m_png,
                    m_info,
                    mat.Width(), mat.Height(),
                    8,
                    PNG_COLOR_TYPE_RGBA,
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT
            );

            png_write_info(m_png, m_info);

            // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
            // Use png_set_filler().
            //png_set_filler(png, 0, PNG_FILLER_AFTER);

            m_rowPointers = new png_bytep[mat.Height()];
            std::vector<T> temp = mat.template DataInType<T>();

            for(unsigned int j = 0; j < mat.Height(); j++)
            {
                m_rowPointers[j] = new png_byte[mat.Width() * 4];
                png_bytep row = m_rowPointers[j];
                for(unsigned int i = 0; i < mat.Width(); i++)
                {
                    png_bytep px = &(row[i * 4]);
                    if(mat.Channel() > 1)
                    {
                        for(unsigned int k = 0; k < 4; k++)
                        {
                            if(k < mat.Channel())
                            {
                                px[k] = static_cast<png_byte>(temp[(j * mat.Width() + i) * mat.Channel() + k]);
                            }
                            else
                            {
                                if(k == 3)
                                    px[k] = 255;
                                else
                                    px[k] = 0;
                            }
                        }
                    }
                    else
                    {
                        px[0] = static_cast<png_byte>(temp[(j * mat.Width() + i) * mat.Channel()]);
                        px[1] = static_cast<png_byte>(temp[(j * mat.Width() + i) * mat.Channel()]);
                        px[2] = static_cast<png_byte>(temp[(j * mat.Width() + i) * mat.Channel()]);
                        px[3] = 255;
                    }
                }
            }

            png_write_image(m_png, m_rowPointers);
            png_write_end(m_png, NULL);
            png_destroy_write_struct(&m_png, &m_info);

            delete[] m_rowPointers;

            fclose(m_file);
        }

        template<class T>
        bool PngParser<T>::Init(ActionType actionType) {
            if(actionType == ActionType::Read)
                m_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            else
                m_png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

            if(!m_png)
            {
                return false;
            }

            if(actionType == ActionType::Read)
                m_file = std::fopen(m_fileName.c_str(), "rb");
            else
                m_file = std::fopen(m_fileName.c_str(), "wb");

            if(!m_file)
            {
                if(actionType == ActionType::Read)
                    png_destroy_read_struct(&m_png, &m_info, nullptr);
                else
                    png_destroy_write_struct(&m_png, &m_info);
                return false;
            }

            m_info = png_create_info_struct(m_png);
            if(!m_info)
            {
                if(actionType == ActionType::Read)
                    png_destroy_read_struct(&m_png, &m_info, nullptr);
                else
                    png_destroy_write_struct(&m_png, &m_info);
                return false;
            }

            if(setjmp(png_jmpbuf(m_png)))
            {
                if(actionType == ActionType::Read)
                    png_destroy_read_struct(&m_png, &m_info, nullptr);
                else
                    png_destroy_write_struct(&m_png, &m_info);
                return false;
            }

            png_init_io(m_png, m_file);
            return true;
        }
    }
}