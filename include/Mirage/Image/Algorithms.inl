namespace mrg
{
    template<class Type>
    Type ScalingNearestNeighbor(uint32_t x, uint32_t y, uint8_t k,
                                const std::vector<Type>& oldData,
                                const ScalingSettings& settings)
    {
        double px = mrg::Floor(x * settings.xRatio);
        double py = mrg::Floor(y * settings.yRatio);

        return oldData[(py * settings.oldWidth + px) * settings.channelNumber + k];
    }

    template<class Type>
    Matrix<Type> Scale(const Matrix<Type>& img, uint32_t nWidth, uint32_t nHeight, ScalingFunction<Type> algorithm)
    {
        uint32_t width   = img.Width();
        uint32_t height  = img.Height();
        uint8_t channel = img.Channel();

        const auto& data = img.Data();
        std::vector<Type> nData = std::vector<Type>((nWidth * nHeight) * channel);
        ScalingSettings settings{img.Width(), img.Height(), nWidth, nHeight, channel,
                                 static_cast<double>(width) / nWidth,
                                 static_cast<double>(height) / nHeight};

        for(uint32_t x = 0; x < nWidth; x++)
        {
            for(uint32_t y = 0; y < nHeight; y++)
            {
                for(uint8_t k = 0; k < channel; k++)
                    nData[(y * nWidth + x) * channel + k] = algorithm(x, y, k, data, settings);
            }
        }
        return Matrix<Type>(nData, nWidth, nHeight, channel);
    }

    template<class Type>
    Matrix<Type> Crop(const Matrix<Type>& img, uint32_t bWidth, uint32_t bHeight, uint32_t eWidth, uint32_t eHeight)
    {
        uint32_t width   = img.Width();
        uint32_t height  = img.Height();
        uint32_t channel = img.Channel();
        const auto& data = img.Data();

        assert(bWidth >= 0   && bWidth <= width);
        assert(bHeight >= 0  && bHeight <= height);
        assert(eWidth >= 0   && eWidth <= width);
        assert(eHeight >= 0  && eHeight <= height);

        uint32_t trueNewWidth   = eWidth - bWidth;
        uint32_t trueNewHeight  = eHeight - bHeight;
        std::vector<Type> nData = std::vector<Type>(trueNewWidth * trueNewHeight * channel);

        for(uint32_t x = 0; x < trueNewWidth; x++)
        {
            for(uint32_t y = 0; y < trueNewHeight; y++)
            {
                uint32_t oldX = x + bWidth;
                uint32_t oldY = y + bHeight;
                for(uint8_t k = 0; k < channel; k++)
                {
                    nData[(y * trueNewWidth + x) * channel + k] =
                            data[(oldY * (width) + oldX) * channel + k];
                }
            }
        }
        return mrg::Matrix<Type>(nData, trueNewWidth, trueNewHeight, channel);
    }
}