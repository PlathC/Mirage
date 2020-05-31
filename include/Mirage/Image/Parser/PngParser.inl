#include <cstdio>
#include <cstdlib>
#include "PngParser.hpp"


namespace mrg
{
    namespace ImageParser
    {
        // Using https://gist.github.com/niw/5963798

        template<typename T>
        Matrix<T> PngParser<T>::Parse(std::string _fileName, const unsigned int channel)
        {
            fileName = _fileName;

            if(!Init(ActionType::Read))
                return Matrix<T>();

            png_read_info(png, info);

            unsigned int width, height;
            width     = static_cast<unsigned int>(png_get_image_width(png, info));
            height    = static_cast<unsigned int>(png_get_image_height(png, info));
            colorType = png_get_color_type(png, info);
            bitDepth  = png_get_bit_depth(png, info);

            if(bitDepth == 16)
                png_set_strip_16(png);

            // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
            if(colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
                png_set_expand_gray_1_2_4_to_8(png);

            if(png_get_valid(png, info, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(png);

            // These color_type don't have an alpha channel then fill it with 0xff.
            if(colorType == PNG_COLOR_TYPE_RGB ||
               colorType == PNG_COLOR_TYPE_GRAY ||
               colorType == PNG_COLOR_TYPE_PALETTE)
                png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

            if(colorType == PNG_COLOR_TYPE_GRAY ||
               colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
                png_set_gray_to_rgb(png);

            png_read_update_info(png, info);

            rowPointers = new png_bytep[height];

            for(unsigned int y = 0; y < height; y++) {
                rowPointers[y] = new png_byte[png_get_rowbytes(png, info)];
            }

            png_read_image(png, rowPointers);
            fclose(file);
            png_destroy_read_struct(&png, &info, nullptr);

            std::vector<T> result(static_cast<unsigned int>(width * height * channel));

            for(unsigned int y = 0; y < height; y++)
            {
                png_bytep row = rowPointers[y];
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

        template<typename T>
        void PngParser<T>::Write(Matrix<T>& mat, std::string _fileName)
        {
            fileName = _fileName;
            if(!Init(ActionType::Write))
                return;

            // Output is 8bit depth, RGBA format.
            png_set_IHDR(
                    png,
                    info,
                    mat.Width(), mat.Height(),
                    8,
                    PNG_COLOR_TYPE_RGBA,
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT
            );

            png_write_info(png, info);

            // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
            // Use png_set_filler().
            //png_set_filler(png, 0, PNG_FILLER_AFTER);

            rowPointers = new png_bytep[mat.Height()];
            std::vector<T>& temp = mat.GetData();

            for(unsigned int j = 0; j < mat.Height(); j++)
            {
                rowPointers[j] = new png_byte[mat.Width() * 4];
                png_bytep row = rowPointers[j];
                for(unsigned int i = 0; i < mat.Width(); i++)
                {
                    png_bytep px = &(row[i * 4]);
                    if(mat.Channel() > 1)
                    {
                        for(unsigned int k = 0; k < 4; k++)
                        {
                            if(k < mat.Channel())
                            {
                                px[k] = temp[(j * mat.Width() + i) * mat.Channel() + k];
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
                        px[0] = temp[(j * mat.Width() + i) * mat.Channel()];
                        px[1] = temp[(j * mat.Width() + i) * mat.Channel()];
                        px[2] = temp[(j * mat.Width() + i) * mat.Channel()];
                        px[3] = temp[255];
                    }
                }
            }

            png_write_image(png, rowPointers);
            png_write_end(png, NULL);
            png_destroy_write_struct(&png, &info);

            delete[] rowPointers;

            fclose(file);
        }

        template<typename T>
        bool PngParser<T>::Init(ActionType actionType) {
            if(actionType == ActionType::Read)
                png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            else
                png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

            if(!png)
            {
                return false;
            }

            if(actionType == ActionType::Read)
                file = std::fopen(fileName.c_str(), "rb");
            else
                file = std::fopen(fileName.c_str(), "wb");
            if(!file)
            {
                free(png);
                return false;
            }

            info = png_create_info_struct(png);
            if(!info)
            {
                png_destroy_write_struct(&png, &info);
                return false;
            }

            if(setjmp(png_jmpbuf(png)))
            {
                if(actionType == ActionType::Write)
                    png_destroy_write_struct(&png, &info);
                return false;
            }

            png_init_io(png, file);
            return true;
        }
    }
}