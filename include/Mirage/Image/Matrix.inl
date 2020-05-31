
namespace mrg {

    template<typename Type>
    Matrix<Type>::Matrix() : m_width(0), m_height(0), m_channelNumber(0), m_data() { }

    template<typename Type>
    Matrix<Type>::Matrix(const uint32_t width, const uint32_t  height, const uint8_t channelNumber) :
    m_width(width),
    m_height(height),
    m_channelNumber(channelNumber),
    m_data()
    {
        this->m_data.resize(width * height * channelNumber);
    }

    template<typename Type>
    Matrix<Type>::Matrix(Type fill, const uint32_t width, const uint32_t height, const uint8_t channelNumber) :
    m_width(width),
    m_height(height),
    m_channelNumber(channelNumber),
    m_data(width * height, fill)
    {
    }

    template<typename Type>
    Matrix<Type>::Matrix(const std::vector<Type>& pixels, const uint32_t width, const uint32_t height, const uint8_t channelNumber) :
    m_width(width),
    m_height(height),
    m_channelNumber(channelNumber),
    m_data(pixels)
    {
    }

    template<typename Type>
    template<std::size_t Size>
    Matrix<Type>::Matrix(const std::array<Type, Size>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber):
    m_width(width),
    m_height(height),
    m_channelNumber(channelNumber),
    m_data()
    {
        m_data.resize(Size);
        for(size_t i = 0; i < Size; i++)
        {
            m_data[i] = pixels[i];
        }
    }

    template<typename Type>
    Matrix<Type>::Matrix(std::initializer_list<Type> pixels, const uint32_t width, const uint32_t height, const uint8_t channelNumber):
    m_width(width),
    m_height(height),
    m_channelNumber(channelNumber),
    m_data()
    {
        m_data.reserve(pixels.size());
        for(auto ite = pixels.begin(); ite != pixels.end(); ite++)
        {
            m_data.push_back(*ite);
        }
    }

    template<typename Type>
    template<typename T>
    Matrix<T> Matrix<Type>::ToGrayScale()
    {
        std::vector<T> resultData;
        resultData.resize(m_width * m_height);

        for(unsigned int x = 0; x < m_width; x++)
        {
            for(unsigned int y = 0; y < m_height; y++)
            {
                double pixel = 0;
                for(unsigned int k = 0; k < m_channelNumber; k++)
                {
                    pixel += m_data[(x * m_height + y) * m_channelNumber + k];
                }
                resultData[x * m_height + y] = static_cast<T>(mrg::Floor(pixel / m_channelNumber));
            }
        }

        return Matrix<T>(resultData, m_width, m_height, 1);
    }

    template<typename Type>
    Matrix<double> Matrix<Type>::Sobel()
    {
        Matrix<double> gray = ToGrayScale<double>();

        const double kernelH[3][3] = {{-1., 0., 1.},
                                      {-2., 0., 2.},
                                      {-1., 0., 1.}};

        const double kernelV[3][3] = {{-1., -2., -1.},
                                      { 0.,  0.,  0.},
                                      { 1.,  2.,  1.}};

        std::vector<double> grayData = gray.GetData();
        auto resultData = std::vector<double>(m_width * m_height);

        for(uint32_t i = 1; i < m_height - 1; i++)
        {
            for(uint32_t j = 1; j < m_width - 1; j++)
            {
                double magnitudeX = 0.;
                double magnitudeY = 0.;
                for(uint8_t ik = 0; ik < 3; ik++)
                {
                    for(uint8_t jk = 0; jk < 3; jk++)
                    {
                        unsigned int xn = i + ik - 1;
                        unsigned int yn = j + jk - 1;

                        unsigned int index = xn * m_width + yn;
                        magnitudeX += grayData[index] * kernelH[ik][jk];
                        magnitudeY += grayData[index] * kernelV[ik][jk];
                    }
                }

                resultData[i * m_width + j] = mrg::Sqrt(magnitudeX * magnitudeX
                                                         + magnitudeY * magnitudeY);
            }
        }

        return Matrix<double>(resultData, m_width, m_height, 1);
    }

    template<typename Type>
    Matrix<double> Matrix<Type>::Canny()
    {
        // Based on https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123

        Matrix<Type> blurred = Convolve(mrg::gaussianBlurKernel5x5);

        Matrix<double> gray = blurred.ToGrayScale<double>();
        const double kernelH[3][3] = {{-1, 0, 1},
                                      {-2, 0, 2},
                                      {-1, 0, 1}};

        const double kernelV[3][3] = {{-1, -2, -1},
                                      { 0,  0,  0},
                                      { 1,  2,  1}};

        std::vector<double> grayData = gray.GetData();
        auto gradientData = std::vector<double>(m_width * m_height);
        auto directionData = std::vector<double>(m_width * m_height);

        double maximumValue = 0;

        for(uint32_t i = 1; i < m_height - 1; i++)
        {
            for(uint32_t j = 1; j < m_width - 1; j++)
            {
                double magnitudeX = 0;
                double magnitudeY = 0;
                for(uint8_t ik = 0; ik < 3; ik++)
                {
                    for(uint8_t jk = 0; jk < 3; jk++)
                    {
                        unsigned int xn = i + ik - 1;
                        unsigned int yn = j + jk - 1;

                        unsigned int index = xn * m_width + yn;
                        magnitudeX += grayData[index] * kernelH[ik][jk];
                        magnitudeY += grayData[index] * kernelV[ik][jk];
                    }
                }

                double currentValue = mrg::Sqrt(magnitudeX * magnitudeX
                                               + magnitudeY * magnitudeY);
                gradientData[i * m_width + j] = currentValue;
                directionData[i * m_width + j] = (mrg::Atan(magnitudeX / magnitudeY) * 180.0) / mrg::Pi;
                if(directionData[i * m_width + j] < 0)
                    directionData[i * m_width + j] += 180;

                if(currentValue > maximumValue)
                    maximumValue = currentValue;
            }
        }

        // Non Maximum Suppression
        auto resultData = std::vector<double>(m_width * m_height);
        for(uint32_t i = 1; i < m_height - 1; i++)
        {
            for(uint32_t j = 1; j < m_width - 1; j++)
            {
                double q = maximumValue;
                double r = maximumValue;
                double currentAngle = directionData[i * m_width + j];

                if(0 <= currentAngle || (157.5 <= currentAngle && currentAngle <= 180))
                {
                    q = directionData[i * m_width + (j + 1)];
                    r = directionData[i * m_width + (j - 1)];
                }
                else if(22.5 <= currentAngle && currentAngle < 67.5)
                {
                    q = directionData[(i+1) * m_width + (j - 1)];
                    r = directionData[(i-1) * m_width + (j + 1)];
                }
                else if(67.5 <= currentAngle && currentAngle < 112.5)
                {
                    q = directionData[(i+1) * m_width + j];
                    r = directionData[(i-1) * m_width + j];
                }
                else if(112.5 <= currentAngle && currentAngle < 157.5)
                {
                    q = directionData[(i-1) * m_width + (j - 1)];
                    r = directionData[(i+1) * m_width + (j + 1)];
                }

                if(gradientData[i * m_width + j] >= q && gradientData[i * m_width + j] >= r)
                    resultData[i * m_width + j] = gradientData[i * m_width + j];
                else
                    resultData[i * m_width + j] = 0;
            }
        }

        // TODO: Avoid matrix reallocation
        resultData = Matrix<double>(resultData, m_width, m_height, 1).Threshold<double>().GetData();

        for(uint32_t i = 1; i < m_height - 1; i++)
        {
            for(uint32_t j = 1; j < m_width - 1; j++)
            {
                if(resultData[i * m_width + j] == 127.0)
                {
                    double ul = resultData[(i-1) * m_width + (j + 1)];
                    double uu = resultData[(i) * m_width + (j + 1)];
                    double ur = resultData[(i+1) * m_width + (j + 1)];
                    double l  = resultData[(i-1) * m_width + (j)];
                    double r  = resultData[(i+1) * m_width + (j)];
                    double dl = resultData[(i-1) * m_width + (j - 1)];
                    double du = resultData[(i) * m_width + (j - 1)];
                    double dr = resultData[(i+1) * m_width + (j - 1)];

                    // TODO: Change 255 to image depth
                    if(ul == 255.0 || uu == 255.0 || ur == 255.0 ||
                       l == 255.0 || r == 255.0 ||
                       dl == 255.0 || du == 255.0 || dr == 255.0)
                        resultData[i * m_width + j] = 255.0;
                    else
                        resultData[i * m_width + j] = 0.0;
                }
            }
        }

        return Matrix<double>(resultData, m_width, m_height, 1);
    }

    template<typename Type>
    template<typename T>
    Matrix<Type> Matrix<Type>::Convolve(Matrix<T> kernel)
    {
        int kernelCenter = Floor(kernel.Width() / 2);
        std::vector<Type> resultData(m_data);

        for(uint32_t i = 0 + kernelCenter; i < m_height - kernelCenter; i++)
        {
            for(uint32_t j = 0 + kernelCenter; j < m_width - kernelCenter; j++)
            {
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    Type value = Type(0);
                    for(uint32_t ik = 0; ik < kernel.Width(); ik++)
                    {
                        for(uint32_t jk = 0; jk < kernel.Height(); jk++)
                        {
                            uint32_t xn = i + ik - kernelCenter;
                            uint32_t yn = j + jk - kernelCenter;

                            uint32_t index = (xn * m_width + yn) * m_channelNumber + k;
                            value += m_data[index] * kernel.Get(ik, jk);
                        }
                    }
                    resultData[(i * m_width + j) * m_channelNumber + k] = value;
                }
            }
        }

        return Matrix<Type>(resultData, m_width, m_height, this->m_channelNumber);
    }

    template<typename Type>
    template<typename T>
    Matrix<T> Matrix<Type>::Threshold() const
    {
        assert(m_channelNumber == 1);

        // http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
        std::map<Type, int> hist;
        for(unsigned int i = 0; i < m_data.size(); i++)
        {
            int h = m_data[i];
            if(hist.count(h) <= 0)
                hist[h] = 0;
            hist[h]++;
        }

        int total = m_data.size();
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
        threshData.resize(m_data.size());
        for(unsigned int i = 0; i < m_data.size(); i++)
        {
            // TODO: Change 256 to image depth
            threshData[i] = (m_data[i] < threshold) ? 0 : 255;
        }

        return Matrix<T>(threshData, m_width, m_height, 1);
    }

    template<typename Type>
    Matrix<Type> Matrix<Type>::HistogramEqualization()
    {
        //https://en.wikipedia.org/wiki/Histogram_equalization#Implementation
        std::vector<Type> resultData = std::vector<Type>((m_width * m_height) * m_channelNumber);

        auto channelArrays = std::vector<std::vector<Type>>(m_channelNumber);

        for(uint8_t k = 0; k < m_channelNumber; k++)
            channelArrays[k] = std::vector<Type>(m_width * m_height);

        for(unsigned int x = 0; x < m_width; x++)
        {
            for(unsigned int y = 0; y < m_height; y++)
            {
                for(unsigned int k = 0; k < m_channelNumber; k++)
                {
                    channelArrays[k][(x * m_height + y)] = m_data[(x * m_height + y) * m_channelNumber + k];
                }
            }
        }

        auto computeEqualization = [=](std::vector<Type> &result) -> void
        {
            std::map<Type, double> normHistogram = ComputeNormalizedHistogram(result, m_width, m_height);
            std::map<Type, double> cumulativeHistogram;

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
                // TODO: Change 256 to image depth
                pixel = (256 - 1) * cumulativeHistogram[pixel];
            }
        };

        for(uint8_t k = 0; k < m_channelNumber; k++)
            computeEqualization(channelArrays[k]);


        for(unsigned int x = 0; x < m_width; x++)
        {
            for(unsigned int y = 0; y < m_height; y++)
            {
                for(unsigned int k = 0; k < m_channelNumber; k++)
                {
                    resultData[(x * m_height + y) * m_channelNumber + k] = channelArrays[k][(x * m_height + y)];
                }
            }
        }

        return Matrix<Type>(resultData, m_width, m_height, m_channelNumber);
    }

    template<typename Type>
    Type Matrix<Type>::Get(unsigned int w, unsigned int h) const
    {
        assert(w < m_width && h < m_height);
        return this->m_data[w * m_height + h];
    }

    template<typename Type>
    std::vector<Type>& Matrix<Type>::GetData()
    {
        return this->m_data;
    }

    template<typename Type>
    template<class ReturnType>
    std::vector<ReturnType> Matrix<Type>::GetRawData() const
    {
        std::vector<ReturnType> rawData = std::vector<ReturnType>(m_width * m_height * m_channelNumber);

        for(unsigned int x = 0; x < m_width; x++)
        {
            for(unsigned int y = 0; y < m_height; y++)
            {
                for(unsigned int k = 0; k < m_channelNumber; k++)
                {
                    rawData[(x * m_height + y) * m_channelNumber + k] =
                            static_cast<ReturnType>(m_data[(x * m_height + y) * m_channelNumber + k]);
                }
            }
        }
        return rawData;
    }

    template<typename Type>
    void Matrix<Type>::Set(uint32_t w, uint32_t h, const Type& t)
    {
        assert(w < m_width);
        assert(h < m_height);
        this->m_data[w * m_height + h] = t;
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
    static std::map<T, double> ComputeNormalizedHistogram(const std::vector<T> &channel, uint32_t width, uint32_t height)
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

