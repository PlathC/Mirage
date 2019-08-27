
namespace mrg {

    template<typename Type>
    Matrix<Type>::Matrix() : width(0), height(0), channelNumber(0), data() { }

    template<typename Type>
    Matrix<Type>::Matrix(const uint32_t width, const uint32_t  height, const uint8_t channelNumber) :
    width(width),
    height(height),
    channelNumber(channelNumber),
    data()
    {
        this->data.resize(width * height);
    }

    template<typename Type>
    Matrix<Type>::Matrix(Type fill, const uint32_t width, const uint32_t height, const uint8_t channelNumber) :
    width(width),
    height(height),
    channelNumber(channelNumber),
    data(width * height, fill)
    {
    }

    template<typename Type>
    Matrix<Type>::Matrix(std::vector<Type>& pixels, const uint32_t width, const uint32_t height, const uint8_t channelNumber) :
    width(width),
    height(height),
    channelNumber(channelNumber),
    data(pixels)
    {
    }

    template<typename Type>
    Matrix<Type>::Matrix(std::initializer_list<Type> pixels, const uint32_t width, const uint32_t height, const uint8_t channelNumber):
    width(width),
    height(height),
    channelNumber(channelNumber),
    data()
    {
        data.reserve(pixels.size());
        for(auto ite = pixels.begin(); ite != pixels.end(); ite++)
        {
            data.push_back(*ite);
        }
    }

    template<typename Type>
    template<typename T>
    Matrix<T> Matrix<Type>::ToGrayScale()
    {
        std::vector<T> resultData;
        resultData.resize(width * height);

        for(size_t i = 0; i < data.size(); i++)
        {
            T temp = 0;
            if constexpr(std::is_arithmetic<Type>::value)
            {
                resultData[i] = static_cast<T>(data[i]);
            }
            else
            {
                for(uint8_t j = 0; j < channelNumber; j++)
                    temp += data[i][j];
                resultData[i] = static_cast<T>(temp/channelNumber);
            }

        }

        Matrix<T> result = Matrix<T>(resultData, width, height, 1);
        return result;
    }

    template<typename Type>
    Matrix<double> Matrix<Type>::Sobel()
    {
        Matrix<double> gray = this->ToGrayScale<double>();

        const double kernelH[3][3] = {{-1, 0, 1},
                                      {-2, 0, 2},
                                      {-1, 0, 1}};

        const double kernelV[3][3] = {{-1, -2, -1},
                                      { 0,  0,  0},
                                      { 1,  2,  1}};

        std::vector<double> grayData = gray.GetData();
        std::vector<double> resultData;
        resultData.resize(width * height);

        for(uint32_t i = 1; i < width - 1; i++)
        {
            for(uint32_t j = 1; j < height - 1; j++)
            {
                double magnitudeX = 0;
                double magnitudeY = 0;
                for(uint8_t ik = 0; ik < 3; ik++)
                {
                    for(uint8_t jk = 0; jk < 3; jk++)
                    {
                        unsigned int xn = i + ik - 1;
                        unsigned int yn = j + jk - 1;

                        unsigned int index = xn * height + yn;
                        magnitudeX += grayData[index] * kernelH[ik][jk];
                        magnitudeY += grayData[index] * kernelV[ik][jk];
                    }
                }

                resultData[i * height + j] = mrg::Sqrt(magnitudeX * magnitudeX
                                                          + magnitudeY * magnitudeY);
            }
        }

        Matrix<double> result = Matrix<double>(resultData, width, height, 1);

        return result;
    }

    template<typename Type>
    template<typename T>
    Matrix<Type> Matrix<Type>::Convolve(Matrix<T> kernel)
    {
        int kernelCenter = Floor(kernel.Width() / 2);
        std::vector<Type> resultData(data);

        for(uint32_t i = 0 + kernelCenter; i < width - kernelCenter; i++)
        {
            for(uint32_t j = 0 + kernelCenter; j < height - kernelCenter; j++)
            {
                Type value = 0;
                for(int ik = 0; ik < kernel.Width(); ik++)
                {
                    for(int jk = 0; jk < kernel.Height(); jk++)
                    {
                        unsigned int xn = i + ik - kernelCenter;
                        unsigned int yn = j + jk - kernelCenter;

                        unsigned int index = xn * height + yn;
                        value += data[index] * kernel.Get(ik, jk);
                    }
                }
                resultData[i * height + j] = value;
            }
        }

        Matrix<Type> result(resultData, width, height, this->channelNumber);
        return result;
    }

    template<typename Type>
    template<typename T>
    Matrix<T> Matrix<Type>::Threshold() const
    {
        assert(channelNumber == 1);

        // http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
        std::map<Type, int> hist;
        for(unsigned int i = 0; i < data.size(); i++)
        {
            int h = data[i];
            if(hist.count(h) <= 0)
                hist[h] = 0;
            hist[h]++;
        }

        int total = data.size();
        float sum = 0;
        for (auto it = hist.begin(); it != hist.end(); it++ )
            sum += it->first * it->second;

        float sumB = 0;
        int weightBackground = 0;
        int weightForeground = 0;

        float varMax = 0;
        Type threshold = Type(0);

        for (auto it = hist.begin(); it != hist.end(); it++ )
        {
            weightBackground += it->second;
            weightForeground = total - weightBackground;
            if(weightForeground == 0) break;

            sumB += static_cast<float>(it->first * it->second);

            float meanBackground = sumB / weightBackground;
            float meanForeground = (sum - sumB) / weightForeground;

            float varBetween = static_cast<float>(weightBackground) * static_cast<float>(weightForeground) *
                              (static_cast<float>(meanBackground) - static_cast<float>(meanForeground)) *
                              (static_cast<float>(meanBackground) - static_cast<float>(meanForeground));

            if(varBetween > varMax)
            {
                varMax = varBetween;
                threshold = it->first;
            }
        }

        std::vector<T> threshData;
        threshData.resize(data.size());
        for(unsigned int i = 0; i < data.size(); i++)
        {
            threshData[i] = (data[i] < threshold) ? 0 : 65535;
        }

        return Matrix<T>(threshData, width, height, 1);
    }

    template<typename Type>
    Matrix<Type> Matrix<Type>::HistogramEqualization()
    {
        std::vector<Type> resultData = std::vector<Type>(this->data);

        if constexpr(std::is_arithmetic<Type>::value)
        {
            //https://en.wikipedia.org/wiki/Histogram_equalization#Implementation
            std::map<Type, double> normHistogram = ComputeNormalizeHistogram(resultData, width, height);
            std::map<Type, double> cumulativeHistogram;

            // Compute cumulative histogram
            double sum = 0;
            for (auto it = normHistogram.begin(); it != normHistogram.end(); it++ )
            {
                sum += normHistogram[it->first];
                cumulativeHistogram[it->first] = sum;
            }

            // Applying equalization
            for(auto& pixel : resultData)
            {
                pixel = (256 - 1) * cumulativeHistogram[pixel];
            }
        }
        else
        {
            //https://en.wikipedia.org/wiki/Histogram_equalization#Of_color_images
            //static_assert("The histogram equalization for color image is not yet implemented.");

            auto t = data[0][0];
            std::vector<decltype(t)> red;
            std::vector<decltype(t)> green;
            std::vector<decltype(t)> blue;

            for(size_t i = 0; i < data.size(); i++)
            {
                red.push_back(data[i][0]);
                green.push_back(data[i][1]);
                blue.push_back(data[i][2]);
            }

            auto computeEqualization = [](std::vector<decltype(t)> &result, uint32_t _width, uint32_t _height) -> void
            {
                std::map<decltype(t), double> normHistogram = ComputeNormalizeHistogram(result, _width, _height);
                std::map<decltype(t), double> cumulativeHistogram;

                // Compute cumulative histogram
                double sum = 0;
                for (auto it = normHistogram.begin(); it != normHistogram.end(); it++ )
                {
                    sum += normHistogram[it->first];
                    cumulativeHistogram[it->first] = sum;
                }

                // Applying equalization
                for(auto& pixel : result)
                {
                    pixel = (256 - 1) * cumulativeHistogram[pixel];
                }
            };

            computeEqualization(red, width, height);
            computeEqualization(green, width, height);
            computeEqualization(blue, width, height);

            for(size_t i = 0; i < data.size(); i++)
            {
                resultData[i][0] = red[i];
                resultData[i][1] = green[i];
                resultData[i][2] = blue[i];
            }
        }

        return Matrix<Type>(resultData, width, height, channelNumber);
    }

    template<typename Type>
    Type& Matrix<Type>::Get(unsigned int w, unsigned int h)
    {
        assert(w < width  && h < height);
        return this->data[w * height + h];
    }

    template<typename Type>
    std::vector<Type>& Matrix<Type>::GetData()
    {
        return this->data;
    }

    template<typename Type>
    template<typename ReturnType>
    ReturnType* Matrix<Type>::GetRawData()
    {
        auto* rawData = new ReturnType[width * height * channelNumber];
        for(unsigned int x = 0; x < width; x++)
        {
            for(unsigned int y = 0; y < height; y++)
            {
                if constexpr(std::is_arithmetic<Type>::value)
                {
                    rawData[y * channelNumber + x * height] = data[x * height + y];
                }else
                {
                    for(unsigned int k = 0; k < channelNumber; k++)
                    {
                        rawData[y + x * height][k] = data[x * height + y][k];
                    }
                }
            }
        }
         return rawData;
    }

    template<typename Type>
    void Matrix<Type>::Set(uint32_t w, uint32_t h, const Type& t)
    {
        this->data[w * height + h] = t;
    }

    template<typename T>
    static std::map<T, int> ComputeHistogram(const std::vector<T> &channel)
    {
        std::map<T, int> hist;
        for(auto pixel : channel)
        {
            if(hist.count(pixel) <= 0)
                hist[pixel] = 0;
            hist[pixel]++;
        }
        return hist;
    }

    template<typename T>
    static std::map<T, double> ComputeNormalizeHistogram(const std::vector<T> &channel, uint32_t width, uint32_t height)
    {
        std::map<T, int> histogram = ComputeHistogram(channel);
        uint32_t totalPixelNumber = height * width;
        std::map<T, double> normHistogram;

        for (auto it = histogram.begin(); it != histogram.end(); it++ )
        {
            double newValue = static_cast<float>(it->second) / static_cast<float>(totalPixelNumber);
            normHistogram[it->first] = newValue;
        }
        return normHistogram;
    }
}

