#include <stdio.h>
#include <stdlib.h>

namespace mrg {
    namespace ImageParser {
        // Using https://gist.github.com/niw/5963798

        template<typename T>
        Matrix<T> PngParser<T>::Parse(std::string fileName, const unsigned int channel)
        {
            unsigned int width, height;
            png_byte colorType;
            png_byte bitDepth;
            png_bytep *rowPointers = NULL;

            png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            if(!png)
            {
                return Matrix<T>();
            }

            FILE *fp = fopen(fileName.c_str(), "rb");
            if(!fp)
            {
                free(png);
                return Matrix<T>();
            }

            png_infop info = png_create_info_struct(png);
            if(!info)
            {
                png_destroy_write_struct(&png, &info);
                return Matrix<T>();
            }

            if(setjmp(png_jmpbuf(png))) abort();

            png_init_io(png, fp);
            png_read_info(png, info);

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
            fclose(fp);
            png_destroy_read_struct(&png, &info, NULL);

            std::vector<T> result;
            result.resize(static_cast<unsigned int>(width * height));

            for(unsigned int y = 0; y < height; y++)
            {
                png_bytep row = rowPointers[y];
                for(unsigned int x = 0; x < width; x++)
                {
                    png_bytep px = &(row[x * 4]);

                    if constexpr(std::is_arithmetic<T>::value)
                    {
                        result.push_back(px[0]);
                    }
                    else
                    {
                        T pixel = T(px[0], px[1], px[2], px[3]);

                        result[x * height + y] = pixel;
                    }
                }
            }

            return Matrix<T>(result, width, height, channel);
        }

        template<typename T>
        void PngParser<T>::Write(Matrix<T>& mat, std::string fileName)
        {
            FILE *fp = fopen(fileName.c_str(), "wb");
            if(!fp)
            {
                return;
            }

            png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            if (!png)
            {
                free(png);
                return;
            }

            png_infop info = png_create_info_struct(png);
            if (!info)
            {
                free(info);
                return;
            }

            if (setjmp(png_jmpbuf(png)))
            {
                png_destroy_write_struct(&png, &info);
                return;
            }

            png_init_io(png, fp);

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

            png_bytep *rowPointers = new png_bytep[mat.Height()];
            std::vector<T> temp = mat.GetData();
            unsigned int height = mat.Height();

            for(unsigned int j = 0; j < mat.Height(); j++)
            {
                rowPointers[j] = new png_byte[mat.Width() * 4];
                png_bytep row = rowPointers[j];
                for(unsigned int i = 0; i < mat.Width(); i++)
                {
                    png_bytep px = &(row[i * 4]);
                    T t = temp[i * height + j];
                    if constexpr(std::is_arithmetic<T>::value) {
                        px[0] = t;
                        px[1] = t;
                        px[2] = t;
                        px[3] = t;
                    }else {
                        px[0] = static_cast<png_byte>(t[0]);
                        px[1] = static_cast<png_byte>(t[1]);
                        px[2] = static_cast<png_byte>(t[2]);
                        px[3] = static_cast<png_byte>(t[3]);
                    }
                }
            }

            png_write_image(png, rowPointers);
            png_write_end(png, NULL);
            png_destroy_write_struct(&png, &info);

            delete[] rowPointers;

            fclose(fp);
        }
    }
}