namespace mrg
{
    template<class Type>
    Type ScalingNearestNeighbor(uint32_t x, uint32_t y, uint8_t k,
                                const std::vector<Type>& oldData,
                                const ScalingSettings& settings)
    {
        uint32_t px = static_cast<uint32_t>(mrg::Floor(x * settings.xRatio));
        uint32_t py = static_cast<uint32_t>(mrg::Floor(y * settings.yRatio));

        return oldData[(py * settings.oldWidth + px) * settings.channelNumber + k];
    }

    template<class Type>
    void Scale(Matrix<Type>& img, const uint32_t nWidth, const uint32_t nHeight, const ScalingFunction<Type> algorithm)
    {
        uint32_t width  = img.Width();
        uint32_t height = img.Height();
        uint8_t channel = img.Channel();

        auto& data = img.Data();
        auto nData = std::vector<Type>(nWidth * nHeight * channel);

        ScalingSettings settings{img.Width(), img.Height(), nWidth, nHeight, channel,
                                 static_cast<double>(width) / nWidth,
                                 static_cast<double>(height) / nHeight};

        for(uint32_t x = 0; x < nWidth; x++)
        {
            for(uint32_t y = 0; y < nHeight; y++)
            {
                for(uint8_t k = 0; k < channel; k++)
                {
                    nData[(y * nWidth + x) * channel + k] = algorithm(x, y, k, data, settings);
                }
            }
        }
        img = Matrix<Type>(nData, nWidth, nHeight, channel);
    }

    template<class Type>
    Matrix<Type> Crop(const Matrix<Type>& img, const Vec2<uint32_t>& p1, const Vec2<uint32_t>& p2)
    {
        assert(p1[0]  <= img.Width());
        assert(p1[1] <= img.Height());
        assert(p2[0]  <= img.Width());
        assert(p2[1] <= img.Height());

        uint32_t width   = img.Width();
        uint32_t height  = img.Height();
        uint8_t channel  = img.Channel();

        Vec2<uint32_t> newSize  = p2 - p1;
        auto result = Matrix<Type>(std::vector<Type>(newSize[0] * newSize[1] * channel),
                                   newSize[0], newSize[1], channel);

        for(uint32_t x = 0; x < newSize[0]; x++)
        {
            for(uint32_t y = 0; y < newSize[1]; y++)
            {
                uint32_t oldX = x + p1[0];
                uint32_t oldY = y + p1[1];
                for(uint8_t k = 0; k < channel; k++)
                {
                    result.Get(x, y, k) = img.Get(oldX, oldY, k);
                }
            }
        }
        return result;
    }

    template<class Type>
    Matrix<Type> Rotate(const Matrix<Type>& img, const double angle)
    {
        assert(img.Width() == img.Height() && "This feature isn't available for non square image.");
        const auto& data = img.Data();
        auto nData = std::vector<Type>(data.size(), 0);
        const int32_t width = static_cast<int32_t>(img.Width());
        const int32_t height = static_cast<int32_t>(img.Height());
        const uint8_t channel = img.Channel();

        const int32_t xCenter = static_cast<int32_t>(mrg::Floor(img.Width()  / 2.));
        const int32_t yCenter = static_cast<int32_t>(mrg::Floor(img.Height() / 2.));

        const float cosValue = mrg::Cos(angle);
        const float sinValue = mrg::Sin(angle);
        for(int32_t i = 0; i < width; i++)
        {
            for(int32_t j = 0; j < height; j++)
            {
                int32_t currentX = (i - xCenter);
                int32_t currentY = (j - yCenter);

                int32_t nX = static_cast<int32_t>(
                        cosValue * currentX + sinValue * currentY + xCenter
                );

                int32_t nY = static_cast<int32_t>(
                        - sinValue * currentX + cosValue * currentY + yCenter
                );

                if(nX >= 0 && nX < width && nY >= 0 && nY < height)
                {
                    for(uint8_t k = 0; k < channel; k++)
                    {
                        nData[(nX * height + nY) * channel + k] =
                                data[(i * height + j) * channel + k];
                    }
                }
            }
        }
        return Matrix<Type>(nData, width, height, channel);
    }
}