namespace mrg
{
    template<class T>
    std::map<T, int> ComputeHistogram(const std::vector<T> &channel)
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

    template<class T>
    std::map<T, double> ComputeNormalizedHistogram(const std::vector<T> &channel, uint32_t width, uint32_t height)
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

    template<class ImageType, class ReturnType>
    Matrix<ReturnType> ToGrayScale(const Matrix<ImageType>& img)
    {
        const uint32_t width = img.Width();
        const uint32_t height = img.Height();
        const uint8_t channel = img.Channel();

        //const auto& data = .Data();
        std::vector<ReturnType> resultData;
        resultData.resize(width * height);

        for(uint32_t y = 0; y < height; y++)
        {
            for(uint32_t x = 0; x < width; x++)
            {
                // Avoid precision loss during conversion
                double pixel = 0.;
                for(uint8_t k = 0; k < channel; k++)
                {
                    pixel += img.Get(x, y, k);
                }
                resultData[y * width + x] = static_cast<ReturnType>(mrg::Floor(pixel / channel));
            }
        }

        return Matrix<ReturnType>(resultData, width, height, 1);
    }

    template<class Type>
    Matrix<double> Sobel(const Matrix<Type>& img)
    {
        const uint32_t width  = img.Width();
        const uint32_t height = img.Height();

        Matrix<double> workingImg;
        if(img.Channel() > 1)
        {
            workingImg = ToGrayScale<Type, double>(img);
        }
        else
        {
            workingImg = Transform<Type, double>(img, [](const Type p) -> double {
                return static_cast<double>(p);
            });
        }

        constexpr std::array<double, 9> kernelH = {
                -1., 0., 1.,
                -2., 0., 2.,
                -1., 0., 1.
        };

        constexpr std::array<double, 9> kernelV = {
                -1., -2., -1.,
                 0.,  0.,  0.,
                 1.,  2.,  1.
        };

        auto resultData = std::vector<double>(width * height);
        for(uint32_t j = 1; j < height - 1; j++)
        {
            for(uint32_t i = 1; i < width - 1; i++)
            {
                double magnitudeX = 0.;
                double magnitudeY = 0.;
                for(uint8_t jk = 0; jk < 3; jk++)
                {
                    for(uint8_t ik = 0; ik < 3; ik++)
                    {
                        const uint32_t yn = j + jk - 1;
                        const uint32_t xn = i + ik - 1;

                        magnitudeX += workingImg.Get(xn, yn) * kernelH[jk * 3 + ik];
                        magnitudeY += workingImg.Get(xn, yn) * kernelV[jk * 3 + ik];
                    }
                }
                resultData[j * width + i] = mrg::Sqrt(magnitudeX * magnitudeX
                                                      + magnitudeY * magnitudeY);
            }
        }

        return Matrix<double>(resultData, width, height);
    }

    template<class Type>
    Matrix<double> Canny(const Matrix<Type>& img)
    {
        // Based on https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
        const uint32_t width  = img.Width();
        const uint32_t height = img.Height();

        Matrix<double> workingImg;
        if(img.Channel() > 1)
        {
            workingImg = ToGrayScale<Type, double>(img);
        }
        else
        {
            workingImg = Transform<Type, double>(img, [](const Type p) -> double {
                return static_cast<double>(p);
            });
        }

        constexpr std::array<double, 9> kernelH = {
                -1., 0., 1.,
                -2., 0., 2.,
                -1., 0., 1.
        };

        constexpr std::array<double, 9> kernelV = {
                -1., -2., -1.,
                0.,  0.,  0.,
                1.,  2.,  1.
        };

        //std::vector<double> grayData = gray.Data();
        auto gradientData = std::vector<double>(width * height);
        auto directionData = std::vector<double>(width * height);
        double maximumValue = 0.;

        for(uint32_t j = 1; j < height - 1; j++)
        {
            for(uint32_t i = 1; i < width - 1; i++)
            {
                double magnitudeX = 0.;
                double magnitudeY = 0.;
                for(uint8_t jk = 0; jk < 3; jk++)
                {
                    for(uint8_t ik = 0; ik < 3; ik++)
                    {
                        const uint32_t yn = j + jk - 1;
                        const uint32_t xn = i + ik - 1;

                        magnitudeX += workingImg.Get(xn, yn) * kernelH[jk * 3 + ik];
                        magnitudeY += workingImg.Get(xn, yn) * kernelV[jk * 3 + ik];
                    }
                }

                double currentValue = mrg::Sqrt(magnitudeX * magnitudeX + magnitudeY * magnitudeY);
                const std::size_t index = j * width + i;
                gradientData[index] = currentValue;
                directionData[index] = (mrg::Atan(magnitudeX / magnitudeY) * 180.) / mrg::Pi;
                if(directionData[index] < 0)
                    directionData[index] += 180.;

                if(currentValue > maximumValue)
                    maximumValue = currentValue;
            }
        }

        // Non Maximum Suppression
        auto resultImg = Matrix<double>(std::vector<double>(width * height), width, height);
        for(uint32_t j = 1; j < height - 1; j++)
        {
            for(uint32_t i = 1; i < width - 1; i++)
            {
                double q = maximumValue;
                double r = maximumValue;
                double currentAngle = directionData[j * width + i];

                if(0 <= currentAngle || (157.5 <= currentAngle && currentAngle <= 180))
                {
                    q = directionData[j * width + (i + 1)];
                    r = directionData[j * width + (i - 1)];
                }
                else if(22.5 <= currentAngle && currentAngle < 67.5)
                {
                    q = directionData[(j+1) * width + (i - 1)];
                    r = directionData[(j-1) * width + (i + 1)];
                }
                else if(67.5 <= currentAngle && currentAngle < 112.5)
                {
                    q = directionData[(j + 1) * width + i];
                    r = directionData[(j - 1) * width + i];
                }
                else if(112.5 <= currentAngle && currentAngle < 157.5)
                {
                    q = directionData[(j - 1) * width + (j - 1)];
                    r = directionData[(j + 1) * width + (j + 1)];
                }

                const double currentValue = gradientData[j * width + i];
                if(currentValue >= q && currentValue >= r)
                    resultImg.Get(i, j) = currentValue;
                else
                    resultImg.Get(i, j) = 0.;
            }
        }

        Otsu(resultImg);

        for(uint32_t j = 1; j < height - 1; j++)
        {
            for(uint32_t i = 1; i < width - 1; i++)
            {
                if(resultImg.Get(i, j) == 127.0)
                {
                    double ul = resultImg.Get(i + 1, j - 1);
                    double uu = resultImg.Get(i + 1, j    );
                    double ur = resultImg.Get(i + 1, j + 1);
                    double l  = resultImg.Get(i,     j - 1);
                    double r  = resultImg.Get(i,     j + 1);
                    double dl = resultImg.Get(i - 1, j - 1);
                    double du = resultImg.Get(i - 1, j    );
                    double dr = resultImg.Get(i - 1, j + 1);

                    // TODO: Change 255 to image depth
                    if(ul == 255.0 || uu == 255.0 || ur == 255.0 ||
                       l  == 255.0 ||                r  == 255.0 ||
                       dl == 255.0 || du == 255.0 || dr == 255.0)
                        resultImg.Get(i, j) = 255.0;
                    else
                        resultImg.Get(i, j) = 0.0;
                }
            }
        }

        return resultImg;
    }

    template<class ImageType, class KernelType>
    Matrix<ImageType> Convolve(const Matrix<ImageType>& img, const Matrix<KernelType>& kernel)
    {
        const uint32_t kernelCenter = static_cast<uint32_t>(mrg::Floor(kernel.Width() / 2));
        const uint32_t width  = img.Width();
        const uint32_t height = img.Height();
        const uint8_t channel = img.Channel();
        auto result = Matrix<ImageType>(std::vector<ImageType>(width * height * channel),
                                        width, height, channel);

        for(uint32_t i = 0 + kernelCenter; i < width - kernelCenter; i++)
        {
            for(uint32_t j = 0 + kernelCenter; j < height - kernelCenter; j++)
            {
                for(uint8_t k = 0; k < channel; k++)
                {
                    ImageType value = ImageType(0);
                    for(uint32_t ik = 0; ik < kernel.Width(); ik++)
                    {
                        for(uint32_t jk = 0; jk < kernel.Height(); jk++)
                        {
                            uint32_t xn = i + ik - kernelCenter;
                            uint32_t yn = j + jk - kernelCenter;

                            value += static_cast<ImageType>(img.Get(xn, yn, k) * kernel.Get(ik, jk));
                        }
                    }
                    result.Get(i, j, k) = value;
                }
            }
        }
        return result;
    }

    template<class ImageType>
    ImageType KernelMax(const Matrix<ImageType>& kernel)
    {
        const auto& data = kernel.Data();
        return *std::max_element(data.begin(), data.end());
    }

    template<class ImageType>
    ImageType KernelMin(const Matrix<ImageType>& kernel)
    {
        const auto& data = kernel.Data();
        return *std::min_element(data.begin(), data.end());
    }

    template <class ImageType>
    Matrix<ImageType> Convolve(Matrix<ImageType>& img, const ConvolvingFunction<ImageType>& convolvingFunction, const uint32_t kernelSize)
    {
        assert(kernelSize < img.Width() && kernelSize < img.Height() && "Kernel size should be lesser than image size.");
        assert(kernelSize % 2 == 1 && "Kernel size should be odd.");

        const uint32_t kernelCenter = static_cast<uint32_t>(mrg::Floor(kernelSize / 2));
        const uint32_t width  = img.Width();
        const uint32_t height = img.Height();
        const uint8_t channel = img.Channel();

        auto result = Matrix<ImageType>(std::vector<ImageType>(width * height * channel),
                                        width, height, channel);
        auto kernel = Matrix<ImageType>(std::vector<ImageType>(kernelCenter * kernelCenter, 0),
                                        kernelCenter, kernelCenter, 1);
        for(uint32_t i = 0 + kernelCenter; i < width - kernelCenter; i++)
        {
            for(uint32_t j = 0 + kernelCenter; j < height - kernelCenter; j++)
            {
                for(uint8_t k = 0; k < channel; k++)
                {
                    ImageType value = ImageType(0);
                    for(uint32_t ik = 0; ik < kernel.Width(); ik++)
                    {
                        for(uint32_t jk = 0; jk < kernel.Height(); jk++)
                        {
                            uint32_t xn = i + ik - kernelCenter;
                            uint32_t yn = j + jk - kernelCenter;

                            kernel.Get(ik, jk) = img.Get(xn, yn, k);
                        }
                    }
                    result.Get(i, j, k) = convolvingFunction(kernel);
                }
            }
        }
        return result;
    }

    template<class ImageType>
    void Otsu(Matrix<ImageType>& img)
    {
        assert(img.Channel() == 1);
        auto& data = img.Data();

        // http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
        //TODO: Change uint32_t to bit depth type
        auto maxElement = *std::max_element(data.begin(), data.end());
        std::vector<ImageType> hist = std::vector<ImageType>(static_cast<std::size_t>(maxElement) + 1, 0);
        for(std::size_t i = 0; i < data.size(); i++)
        {
            hist[static_cast<std::size_t>(data[i])]++;
        }

        double sum = 0;
        for (std::size_t i = 0; i < hist.size(); i++)
            sum += i * hist[i];

        const std::size_t total = data.size();
        double sumB = 0.;
        double varMax = 0.;
        ImageType weightBackground = 0;
        ImageType weightForeground = 0;
        ImageType threshold = ImageType(0);
        for (std::size_t i = 0; i < hist.size(); i++)
        {
            weightBackground += hist[i];
            weightForeground = total - weightBackground;
            if(weightForeground == 0) break;

            sumB += static_cast<double>(i * hist[i]);

            double meanBackground = sumB / static_cast<double>(weightBackground);
            double meanForeground = (sum - sumB) / static_cast<double>(weightForeground);

            double varBetween = static_cast<double>(weightBackground) * static_cast<double>(weightForeground) *
                                (meanBackground - meanForeground) * (meanBackground - meanForeground);

            if(varBetween > varMax)
            {
                varMax = varBetween;
                threshold = static_cast<ImageType>(i);
            }
        }

        for(std::size_t i = 0; i < data.size(); i++)
        {
            // TODO: Change 256 to image depth
            data[i] = (data[i] < threshold) ? 0 : 255;
        }
    }

    template<class ImageType>
    void HistogramEqualization(Matrix<ImageType>& img)
    {
        const uint32_t width  = img.Width();
        const uint32_t height = img.Height();
        const uint8_t channel = img.Channel();
        auto& data = img.Data();

        //https://en.wikipedia.org/wiki/Histogram_equalization#Implementation
        auto channelArrays = std::vector<std::vector<ImageType>>(channel);

        for(uint8_t k = 0; k < channel; k++)
            channelArrays[k] = std::vector<ImageType>(width * height);

        for(unsigned int x = 0; x < width; x++)
        {
            for(unsigned int y = 0; y < height; y++)
            {
                for(unsigned int k = 0; k < channel; k++)
                {
                    channelArrays[k][(x * height + y)] = data[(x * height + y) * channel + k];
                }
            }
        }

        auto computeEqualization = [=](std::vector<ImageType>& result) -> void
        {
            std::map<ImageType, double> normHistogram = ComputeNormalizedHistogram(result, width, height);
            std::map<ImageType, double> cumulativeHistogram;

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
                pixel = static_cast<ImageType>((256 - 1) * cumulativeHistogram[pixel]);
            }
        };

        for(uint8_t k = 0; k < channel; k++)
            computeEqualization(channelArrays[k]);


        for(unsigned int x = 0; x < width; x++)
        {
            for(unsigned int y = 0; y < height; y++)
            {
                for(unsigned int k = 0; k < channel; k++)
                {
                    data[(x * height + y) * channel + k] = channelArrays[k][(x * height + y)];
                }
            }
        }
    }

    template<class ImageType>
    mrg::Matrix<std::complex<float>> DFT(const mrg::Matrix<ImageType>& img, bool inverse)
    {
        const float inverted = inverse ? 1.f : -1.f;

        mrg::Matrix<ImageType> workingCopy = img;
        if(inverse)
        {
            IFFTShift(workingCopy);
        }

        const auto& data = workingCopy.Data();
        const auto width = workingCopy.Width();
        const auto height = workingCopy.Height();
        const int32_t iWidth = static_cast<int32_t>(workingCopy.Width());
        const int32_t iHeight = static_cast<int32_t>(workingCopy.Height());

        auto result = std::vector<std::complex<float>>(data.size());

        const auto divider = inverse ? 1.f / static_cast<float>(width * height) : 1.f;

        #pragma omp parallel for
        for(int32_t u = 0; u < iWidth; u++)
        {
            for(int32_t v = 0; v < iHeight; v++)
            {
                std::complex<float> sum = {0.f, 0.f};
                for(std::size_t x = 0; x < width; x++)
                {
                    for(std::size_t y = 0; y < height; y++)
                    {
                        const float angle = inverted * 2.f * static_cast<float>(mrg::Pi) *
                                            ( u * static_cast<float>(x) / static_cast<float>(width)
                                            + v * static_cast<float>(y) / static_cast<float>(height));
                        const std::complex<float> exponential = {
                                static_cast<float>(mrg::Cos(angle)),
                                static_cast<float>(mrg::Sin(angle))
                        };

                        const auto dataSample = data[(x * height) + y];
                        std::complex<float> currentData;
                        if constexpr (std::is_same_v<std::complex<float>, ImageType>)
                        {
                            currentData = dataSample;
                        }
                        else
                        {
                            currentData = std::complex<float>(static_cast<float>(dataSample), 0);
                        }

                        sum += currentData * exponential;
                    }
                }
                result[(u * height) + v] = sum * divider;
            }
        }

        auto resultImage = mrg::Matrix<std::complex<float>>(result, width, height, 1);
        if(!inverse)
        {
            FFTShift(resultImage);
        }

        return resultImage;
    }

    static std::tuple<uint32_t, uint32_t> FindPaddingSize(uint32_t paddingSize)
    {
        if(paddingSize % 2 == 0)
        {
            const auto half = static_cast<uint32_t>(paddingSize / 2.f);
            return {half, half};
        }
        else
        {
            const auto firstHalf = static_cast<uint32_t>(std::floor(paddingSize / 2.f));
            return {firstHalf, paddingSize - firstHalf};
        }
    };

    template<class ImageType>
    mrg::Matrix<ImageType> ZeroPadding(const mrg::Matrix<ImageType>& img, const uint32_t newWidth, const uint32_t newHeight)
    {
        assert(img.Channel() == 1 && "This function works only on grayscale images.");

        const auto widthPaddingSize = (newWidth - img.Width());
        const auto heightPaddingSize = (newHeight - img.Height());

        auto [ bottomPadding, topPadding ] = FindPaddingSize(widthPaddingSize);
        auto [ leftPadding, rightPadding ] = FindPaddingSize(heightPaddingSize);

        std::vector<ImageType> newData = std::vector<ImageType>(newWidth * newHeight, 0);
        for(uint32_t i = leftPadding; i < newWidth - rightPadding; i++)
        {
            for(uint32_t j = bottomPadding; j < newHeight - topPadding; j++)
            {
                newData[i * newHeight + j] = img.Get({i - leftPadding, j - bottomPadding}, 0);
            }
        }
        return mrg::Matrix<ImageType>(newData, newWidth, newHeight, 1);
    }

    template<class ImageType>
    mrg::Matrix<ImageType> CropZeroPadding(const mrg::Matrix<ImageType>& img, uint32_t oldWidth, uint32_t oldHeight)
    {
        assert(oldWidth < img.Width() && "Old width should be lesser than current width");
        assert(oldHeight < img.Height() && "Old height should be lesser than current height");

        const auto widthPaddingSize = (img.Width() - oldWidth);
        const auto heightPaddingSize = (img.Height() - oldHeight);
        auto [ bottomPadding, topPadding ] = FindPaddingSize(widthPaddingSize);
        auto [ leftPadding, rightPadding ] = FindPaddingSize(heightPaddingSize);

        auto recoveredData = std::vector<ImageType>(oldWidth * oldHeight);
        const auto& toCropData = img.Data();

        for(uint32_t i = leftPadding; i < img.Width() - rightPadding; i++)
        {
            for(uint32_t j = bottomPadding; j < img.Height() - topPadding; j++)
            {
                recoveredData[(i - leftPadding) * oldWidth + (j - bottomPadding)] = toCropData[i * img.Height() + j];
            }
        }

        return mrg::Matrix<ImageType>(recoveredData, oldWidth, oldHeight, 1);
    }

    template<class ImageType>
    mrg::Matrix<std::complex<float>> FFT2(const mrg::Matrix<ImageType>& img, bool inverse)
    {
        // Mainly based on http://paulbourke.net/miscellaneous/dft/
        mrg::Matrix<ImageType> workingImg = img;
        if(!IsPowerOf2(workingImg.Width()) || !IsPowerOf2(workingImg.Height()))
        {
            const auto newWidth = FindNextHighestPowerOf2(workingImg.Width());
            const auto newHeight = FindNextHighestPowerOf2(workingImg.Height());

            workingImg = ZeroPadding(workingImg, newWidth, newHeight);
        }

        if(inverse)
        {
            IFFTShift(workingImg);
        }

        auto resultData = std::vector<std::complex<float>>(workingImg.Width() * workingImg.Height());

        // Rows fft
        auto currentRow = std::vector<ImageType>(workingImg.Width());
        for(uint32_t j = 0; j < workingImg.Height(); j++)
        {
            for(uint32_t i = 0; i < workingImg.Width(); i++)
            {
                currentRow[i] = workingImg.Get({i, j}, 0);
            }

            auto fftResult = FFT(currentRow, inverse);
            for(uint32_t i = 0; i < workingImg.Width(); i++)
            {
                resultData[i * workingImg.Height() + j] = fftResult[i];
            }
        }

        // Columns
        auto currentColumn = std::vector<std::complex<float>>(workingImg.Height());
        for(uint32_t i = 0; i < workingImg.Width(); i++)
        {
            for(uint32_t j = 0; j < workingImg.Height(); j++)
            {
                currentColumn[j] = resultData[i * workingImg.Height() + j];
            }

            auto fftResult = FFT(currentColumn, inverse);
            for(uint32_t j = 0; j < workingImg.Height(); j++)
            {
                resultData[i * workingImg.Height() + j] = fftResult[j];
            }
        }

        auto result = mrg::Matrix<std::complex<float>>(resultData, workingImg.Width(), workingImg.Height(), 1);

        if(!inverse)
        {
            FFTShift(result);
        }

        if(!IsPowerOf2(img.Width()) || !IsPowerOf2(img.Height()))
            result = CropZeroPadding(result, img.Width(), img.Height());

        return result;
    }

    template<class ImageType>
    std::vector<std::complex<float>> FFT(const std::vector<ImageType>& data, bool inverse)
    {
        // Mainly based on https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
        assert(IsPowerOf2(static_cast<uint32_t>(data.size())) && "Input array size should be a power of 2");
        const float inverted = inverse ? -1.f : 1.f;

        uint8_t powerOf2 = FindPowerOf2(static_cast<uint32_t>(data.size()));
        std::deque<bool> toBeReversed = std::deque<bool>(powerOf2, 0);

        const auto numberToDeque = [](uint32_t number, std::deque<bool>& out)
        {
            for(std::size_t i = 0; i < out.size(); i++)
            {
                out[i] = number & 1;
                number >>= 1;
            }
        };

        const auto dequeToNumber = [](const std::deque<bool>& input) {
            uint32_t result = 0;
            for(std::size_t i = 0; i < input.size(); i++)
            {
                if(input[i])
                {
                    result += 1 << i;
                }
            }
            return result;
        };;
        // Reverse bit copy
        auto bitReversedInputComplex = std::vector<std::complex<float>>(data.size());
        for(uint32_t k = 0; k < data.size(); k++)
        {
            numberToDeque(k, toBeReversed);
            BitsetReverse(toBeReversed);
            uint32_t reversedNumber = dequeToNumber(toBeReversed);
            if constexpr (std::is_same_v<std::complex<float>, ImageType>)
            {
                bitReversedInputComplex[reversedNumber] = data[k];
            }
            else
            {
                bitReversedInputComplex[reversedNumber] = std::complex<float>(data[k], 0.f);
            }
        }

        for(uint32_t s = 1; s <= std::log2(data.size()); s++)
        {
            const uint32_t m = 1 << s;
            float angle = inverted * 2.f * static_cast<float>(mrg::Pi) / static_cast<float>(m);
            std::complex<float> mExponential = {
                    static_cast<float>(mrg::Cos(angle)),
                    static_cast<float>(mrg::Sin(angle))
            };

            for(uint32_t k = 0; k < data.size(); k += m)
            {
                std::complex<float> currentExponential = {1.f, 0.f};
                for(uint32_t j = 0; j < m / 2; j++)
                {
                    const std::complex<float> t = currentExponential * bitReversedInputComplex[k + j + (m / 2)];
                    const std::complex<float> u = bitReversedInputComplex[k + j];
                    bitReversedInputComplex[k + j] = u + t;
                    bitReversedInputComplex[k + j + (m / 2)] = u - t;
                    currentExponential = currentExponential * mExponential;
                }
            }
        }

        if(inverse)
        {
            for(auto& p : bitReversedInputComplex)
                p /= std::complex<float>(static_cast<float>(data.size()));
        }

        return bitReversedInputComplex;
    }

    template<class ImageType>
    void FFTShift(Matrix<ImageType>& img)
    {
        const auto width = img.Width();
        const auto height = img.Height();
        assert(img.Channel() == 1 && "FFTShift only works on grayscale images");

        const uint32_t xShiftValue = static_cast<uint32_t>(std::ceil(width / 2.));
        const uint32_t yShiftValue = static_cast<uint32_t>(std::ceil(height / 2.));

        const auto save = img.Data();

        for(uint32_t x = 0; x < width - xShiftValue; x++)
        {
            for(uint32_t y = 0; y < height - yShiftValue; y++)
            {
                ImageType value = img.Get({x, y}, 0);
                img.Get({x, y}, 0) = img.Get({x + xShiftValue, y + yShiftValue}, 0);
                img.Get({x + xShiftValue, y + yShiftValue}, 0) = value;
            }
        }

        for(uint32_t x = 0; x < width - xShiftValue; x++)
        {
            for(uint32_t y = 0; y < height - yShiftValue; y++)
            {
                ImageType value = img.Get({x + xShiftValue, y}, 0);
                img.Get({x + xShiftValue, y}, 0) = img.Get({x, y + yShiftValue}, 0);
                img.Get({x, y + yShiftValue}, 0) = value;
            }
        }
    }

    template<class ImageType>
    void IFFTShift(Matrix<ImageType>& img)
    {
        assert(img.Channel() == 1 && "IFFTShift only works on grayscale images");

        const auto width = img.Width();
        const auto height = img.Height();
        const uint32_t xShiftValue = static_cast<uint32_t>(std::floor(width / 2.));
        const uint32_t yShiftValue = static_cast<uint32_t>(std::floor(height / 2.));

        const auto save = img.Data();

        for(uint32_t x = 0; x < width - xShiftValue; x++)
        {
            for(uint32_t y = 0; y < height - yShiftValue; y++)
            {
                ImageType value = img.Get({x + xShiftValue, y + yShiftValue}, 0);
                img.Get({x + xShiftValue, y + yShiftValue}, 0) = img.Get({x, y}, 0);
                img.Get({x, y}, 0) = value;
            }
        }

        for(uint32_t x = 0; x < width - xShiftValue; x++)
        {
            for(uint32_t y = 0; y < height - yShiftValue; y++)
            {
                ImageType value = img.Get({x, y + yShiftValue}, 0);
                img.Get({x, y + yShiftValue}, 0) = img.Get({x + xShiftValue, y}, 0);
                img.Get({x + xShiftValue, y}, 0) = value;
            }
        }

    }

    template<uint8_t kernelSize>
    Matrix<double> GenerateGaussianKernel(const int sigma)
    {
        assert(kernelSize % 2 != 0 && "The kernel k must be odd.");

        auto k = static_cast<uint8_t>(mrg::Floor(static_cast<double>(kernelSize) / 2.0));
        std::vector<double> resultKernel { kernelSize };

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