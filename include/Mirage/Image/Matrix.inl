#include <map>

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
        data.resize(pixels.size());
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
                for(unsigned int ik = 0; ik < 3; ik++)
                {
                    for(unsigned int jk = 0; jk < 3; jk++)
                    {
                        unsigned int xn = i + ik - 1;
                        unsigned int yn = j + jk - 1;

                        unsigned int index = xn * height + yn;
                        magnitudeX += grayData[index] * kernelH[ik][jk];
                        magnitudeY += grayData[index] * kernelV[ik][jk];
                    }
                }

                resultData[i * height + j] = Sqrt<double>(magnitudeX * magnitudeX
                                                          + magnitudeY * magnitudeY);
            }
        }

        Matrix<double> result = Matrix<double>(resultData, width, height, 1);

        return result;
    }

    template<typename Type>
    template<typename T>
    Matrix<Type> Matrix<Type>::Convolve(Matrix<T> kernel) const
    {
        int kernelCenter = Floor(kernel.Width() / 2);

        std::vector<Type> resultData;
        resultData.resize(height * width);

        for(int i = 0 + kernelCenter; i < width - kernelCenter; i++)
        {
            for(int j = 0 + kernelCenter; j < height - kernelCenter; j++)
            {

                resultData[i * height + j] = 0;
                for(int ik = (0-kernelCenter); ik < kernelCenter; ik++)
                {
                    for(int jk = (0-kernelCenter); jk < kernelCenter; jk++)
                    {
                        resultData[i * height + j] += data[(i + ik) * height + (j + jk)] * kernel.Get(ik + kernelCenter, jk + kernelCenter);
                    }
                }
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
}