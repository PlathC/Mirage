
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
    template<std::size_t Size>
    Matrix<Type>::Matrix(const std::array<Type, Size>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber):
    width(width),
    height(height),
    channelNumber(channelNumber),
    data()
    {
        data.resize(Size);
        for(size_t i = 0; i < Size; i++)
        {
            data[i] = pixels[i];
        }
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

        return Matrix<T>(resultData, width, height, 1);
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

        return Matrix<double>(resultData, width, height, 1);
    }

    template<typename Type>
    Matrix<double> Matrix<Type>::Canny()
    {
        // Based on https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123

        Matrix<Type> blurred = this->Convolve(mrg::gaussianBlurKernel5x5);

        Matrix<double> gray = blurred.ToGrayScale<double>();
        const double kernelH[3][3] = {{-1, 0, 1},
                                      {-2, 0, 2},
                                      {-1, 0, 1}};

        const double kernelV[3][3] = {{-1, -2, -1},
                                      { 0,  0,  0},
                                      { 1,  2,  1}};
        std::vector<double> grayData = gray.GetData();

        std::vector<double> gradientData;
        gradientData.resize(width * height);
        std::vector<double> directionData;
        directionData.resize(width * height);
        double maximumValue = 0;

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

                double currentValue = mrg::Sqrt(magnitudeX * magnitudeX
                                               + magnitudeY * magnitudeY);
                gradientData[i * height + j] = currentValue;
                directionData[i * height + j] = (mrg::Atan(magnitudeX / magnitudeY) * 180.0) / mrg::Pi;
                if(directionData[i * height + j] < 0)
                    directionData[i * height + j] += 180;

                if(currentValue > maximumValue)
                    maximumValue = currentValue;
            }
        }

        // Non Maximum Suppression
        auto resultData = std::vector<double>(width * height);
        for(uint32_t i = 1; i < width-1; i++)
        {
            for(uint32_t j = 1; j < height-1; j++)
            {
                double q = maximumValue;
                double r = maximumValue;
                double currentAngle = directionData[i * height + j];

                if(0 <= currentAngle || (157.5 <= currentAngle && currentAngle <= 180))
                {
                    q = directionData[i * height + (j+1)];
                    r = directionData[i * height + (j-1)];
                }
                else if(22.5 <= currentAngle && currentAngle < 67.5)
                {
                    q = directionData[(i+1) * height + (j-1)];
                    r = directionData[(i-1) * height + (j+1)];
                }
                else if(67.5 <= currentAngle && currentAngle < 112.5)
                {
                    q = directionData[(i+1) * height + j];
                    r = directionData[(i-1) * height + j];
                }
                else if(112.5 <= currentAngle && currentAngle < 157.5)
                {
                    q = directionData[(i-1) * height + (j-1)];
                    r = directionData[(i+1) * height + (j+1)];
                }

                if(gradientData[i * height + j] >= q && gradientData[i * height + j] >= r)
                    resultData[i * height + j] = gradientData[i * height + j];
                else
                    resultData[i * height + j] = 0;
            }
        }


        double highThreshold = maximumValue * 0.09;
        double lowThreshold = highThreshold * 0.05;

        for(double &i : resultData)
        {
            if(i <= lowThreshold)
                i = 0.0;
            else if(lowThreshold < i && i < highThreshold)
                i = 127.0;
            else
                i = 255.0;
        }

        for(uint32_t i = 1; i < width-1; i++)
        {
            for(uint32_t j = 1; j < height-1; j++)
            {
                if(resultData[i * height + j] == 127.0)
                {
                    double ul = resultData[(i-1) * height + (j+1)];
                    double uu = resultData[(i) * height + (j+1)];
                    double ur = resultData[(i+1) * height + (j+1)];
                    double l  = resultData[(i-1) * height + (j)];
                    double r  = resultData[(i+1) * height + (j)];
                    double dl = resultData[(i-1) * height + (j-1)];
                    double du = resultData[(i) * height + (j-1)];
                    double dr = resultData[(i+1) * height + (j-1)];

                    if(ul == 255.0 || uu == 255.0 || ur == 255.0 ||
                       l == 255.0 || r == 255.0 ||
                       dl == 255.0 || du == 255.0 || dr == 255.0)
                        resultData[i * height + j] = 255.0;
                    else
                        resultData[i * height + j] = 0.0;
                }
            }
        }

        return Matrix<double>(resultData, width, height, 1);
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
                Type value = Type(0);
                for(uint32_t ik = 0; ik < kernel.Width(); ik++)
                {
                    for(uint32_t jk = 0; jk < kernel.Height(); jk++)
                    {
                        uint32_t xn = i + ik - kernelCenter;
                        uint32_t yn = j + jk - kernelCenter;

                        uint32_t index = xn * height + yn;
                        value += data[index] * kernel.Get(ik, jk);
                    }
                }
                resultData[i * height + j] = value;
            }
        }

        return Matrix<Type>(resultData, width, height, this->channelNumber);
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

            float meanBackground = sumB / static_cast<float>(weightBackground);
            float meanForeground = (sum - sumB) / static_cast<float>(weightForeground);

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
        //https://en.wikipedia.org/wiki/Histogram_equalization#Implementation

        std::vector<Type> resultData = std::vector<Type>(this->data);

        if constexpr(std::is_arithmetic<Type>::value)
        {
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
    Type Matrix<Type>::Get(unsigned int w, unsigned int h) const
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
        assert(w < width);
        assert(h < height);
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

    template<uint8_t kernelSize>
    static Matrix<double> GenerateGaussianKernel(int sigma)
    {
        assert(kernelSize % 2 != 0 && "The kernel k must be odd.");
        auto k = static_cast<uint8_t>(mrg::Floor(static_cast<double>(kernelSize) / 2.0));
        std::vector<double> resultKernel{kernelSize};

        for(uint8_t i = 1; i <= kernelSize; i++)
        {
            for(uint8_t j = 1; j <= kernelSize; j++)
            {
                double f = (1.0/(2.0 * mrg::Pi * sigma * sigma));
                auto n = static_cast<double>(mrg::Pow(i - (k + 1), 2) + mrg::Pow(j - (k + 1), 2));
                auto d = static_cast<double>(2 * sigma * sigma);
                resultKernel[(i-1) * kernelSize + (j-1)] = f * mrg::Exp(- n / d);
            }
        }
        return Matrix<double>(resultKernel, kernelSize, kernelSize, 1);
    }

}

