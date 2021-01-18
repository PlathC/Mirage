namespace mrg {

    template<class Type>
    Matrix<Type>::Matrix() : m_width(0), m_height(0), m_channelNumber(0), m_data() { }

    template<class Type>
    Matrix<Type>::Matrix(const uint32_t width, const uint32_t  height, const uint8_t channelNumber) :
        m_width(width),
        m_height(height),
        m_channelNumber(channelNumber),
        m_data()
    {
        this->m_data.resize(width * height * channelNumber);
    }

    template<class Type>
    Matrix<Type>::Matrix(Type fill, const uint32_t width, const uint32_t height, const uint8_t channelNumber) :
        m_width(width),
        m_height(height),
        m_channelNumber(channelNumber),
        m_data(width * height, fill)
    {
    }

    template<class Type>
    Matrix<Type>::Matrix(const std::vector<Type>& pixels, const uint32_t width, const uint32_t height, const uint8_t channelNumber) :
        m_width(width),
        m_height(height),
        m_channelNumber(channelNumber),
        m_data()
    {
        m_data.reserve(pixels.size());
        std::copy(pixels.begin(), pixels.end(), std::back_inserter(m_data));
    }

    template<class Type>
    template<std::size_t Size>
    Matrix<Type>::Matrix(const std::array<Type, Size>& pixels, uint32_t width, uint32_t height, uint8_t channelNumber):
        m_width(width),
        m_height(height),
        m_channelNumber(channelNumber),
        m_data()
    {
        std::copy(pixels.begin(), pixels.end(), std::back_inserter(m_data));
    }

    template<class Type>
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

    template<class Type>
    Matrix<Type> Matrix<Type>::operator*(const Matrix& mask)
    {
        assert(mask.Width( ) <= m_width  && "The mask shouldn't be bigger than the image");
        assert(mask.Height() <= m_height && "The mask shouldn't be bigger than the image");

        Matrix<Type> result = Matrix<Type>(*this);
        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                if(i < mask.Width() && j < mask.Height())
                {
                    for(uint8_t k = 0; k < m_channelNumber; k++)
                    {
                        result.Get({i, j}, k) *= mask.Get({i, j}, k);
                    }
                }
                else if(i >= mask.Width() && j >= mask.Height())
                {
                    break;
                }
            }
        }
        return result;
    }

    template<class Type>
    Matrix<Type> Matrix<Type>::operator*(Type scalar)
    {
        Matrix<Type> result = Matrix<Type>(*this);
        for(auto& p : result.m_data)
        {
            p *= scalar;
        }
        return result;
    }

    template<class Type>
    Matrix<Type>& Matrix<Type>::operator*=(const Matrix& mask)
    {
        assert(mask.Width( ) <= m_width  && "The mask shouldn't be bigger than the image");
        assert(mask.Height() <= m_height && "The mask shouldn't be bigger than the image");

        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                if(i < mask.Width() && j < mask.Height())
                {
                    for(uint8_t k = 0; k < m_channelNumber; k++)
                    {
                        Get({i, j}, k) *= mask.Get({i, j}, k);
                    }
                }
                else if(i >= mask.Width() && j >= mask.Height())
                {
                    break;
                }
            }
        }
        return *this;
    }

    template<class Type>
    Matrix<Type>& Matrix<Type>::operator*=(Type scalar)
    {
        for(auto& p : m_data)
        {
            p *= scalar;
        }
        return *this;
    }

    template<class Type>
    Matrix<Type> Matrix<Type>::operator+(const Matrix& mask)
    {
        assert(mask.Width( ) <= m_width  && "The mask shouldn't be bigger than the image");
        assert(mask.Height() <= m_height && "The mask shouldn't be bigger than the image");

        Matrix<Type> result = Matrix<Type>(*this);

        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                if(i < mask.Width() && j < mask.Height())
                {
                    for(uint8_t k = 0; k < m_channelNumber; k++)
                    {
                        result.Get({i, j}, k) += mask.Get({i, j}, k);
                    }
                }
                else if(i >= mask.Width() && j >= mask.Height())
                {
                    break;
                }
            }
        }
        return result;
    }

    template<class Type>
    Matrix<Type> Matrix<Type>::operator+(Type scalar)
    {
        Matrix<Type> result = Matrix<Type>(*this);
        for(auto& p : result.m_data)
        {
            p += scalar;
        }
        return result;
    }

    template<class Type>
    Matrix<Type>& Matrix<Type>::operator+=(const Matrix<Type>& mask)
    {
        assert(mask.Width( ) <= m_width  && "The mask shouldn't be bigger than the image");
        assert(mask.Height() <= m_height && "The mask shouldn't be bigger than the image");

        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                if(i < mask.Width() && j < mask.Height())
                {
                    for(uint8_t k = 0; k < m_channelNumber; k++)
                    {
                        Get({i, j}, k) += mask.Get({i, j}, k);
                    }
                }
                else if(i >= mask.Width() && j >= mask.Height())
                {
                    break;
                }
            }
        }
        return *this;
    }

    template<class Type>
    Matrix<Type>& Matrix<Type>::operator+=(Type scalar)
    {
        for(auto& p : m_data)
        {
            p += scalar;
        }
        return *this;
    }

    template<class Type>
    std::vector<Vec2<uint32_t>> Matrix<Type>::operator>(Type scalar)
    {
        std::vector<Vec2<uint32_t>> result;
        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                Type currentValue{};
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    currentValue += Get({i, j}, k);
                }
                currentValue /= m_channelNumber;

                if(currentValue > scalar)
                    result.emplace_back(std::initializer_list<uint32_t>{i, j});
            }
        }
        return result;
    }

    template<class Type>
    std::vector<Vec2<uint32_t>> Matrix<Type>::operator<(Type scalar)
    {
        std::vector<Vec2<uint32_t>> result;
        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                Type currentValue{};
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    currentValue += Get({i, j}, k);
                }
                currentValue /= m_channelNumber;

                if(currentValue < scalar)
                    result.emplace_back(std::initializer_list<uint32_t>{i, j});
            }
        }
        return result;
    }

    template<class Type>
    std::vector<Vec2<uint32_t>> Matrix<Type>::operator>=(Type scalar)
    {
        std::vector<Vec2<uint32_t>> result;
        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                Type currentValue{};
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    currentValue += Get({i, j}, k);
                }
                currentValue /= m_channelNumber;

                if(currentValue >= scalar)
                    result.emplace_back(std::initializer_list<uint32_t>{i, j});
            }
        }
        return result;
    }

    template<class Type>
    std::vector<Vec2<uint32_t>> Matrix<Type>::operator<=(Type scalar)
    {
        std::vector<Vec2<uint32_t>> result;
        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                Type currentValue{};
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    currentValue += Get({i, j}, k);
                }
                currentValue /= m_channelNumber;

                if(currentValue <= scalar)
                    result.emplace_back(std::initializer_list<uint32_t>{i, j});
            }
        }
        return result;
    }

    template<class Type>
    std::vector<Vec2<uint32_t>> Matrix<Type>::operator!=(Type scalar)
    {
        std::vector<Vec2<uint32_t>> result;
        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                Type currentValue{};
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    currentValue += Get({i, j}, k);
                }
                currentValue /= m_channelNumber;

                if(currentValue != scalar)
                    result.emplace_back(std::initializer_list<uint32_t>{i, j});
            }
        }
        return result;
    }

    template<class Type>
    std::vector<Vec2<uint32_t>> Matrix<Type>::operator==(Type scalar)
    {
        std::vector<Vec2<uint32_t>> result;
        for(uint32_t i = 0; i < m_width; i++)
        {
            for(uint32_t j = 0; j < m_height; j++)
            {
                Type currentValue{};
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    currentValue += Get({i, j}, k);
                }
                currentValue /= m_channelNumber;

                if(currentValue == scalar)
                    result.emplace_back(std::initializer_list<uint32_t>{i, j});
            }
        }
        return result;
    }

    template<class Type>
    PixelArrayReference<Type> Matrix<Type>::operator[](const std::vector<Vec2<uint32_t>>& indices)
    {
        auto pixels = std::vector<std::reference_wrapper<Type>>();
        pixels.reserve(indices.size());
        for(std::size_t i = 0; i < indices.size(); i++)
        {
            for(uint8_t k = 0; k < m_channelNumber; k++)
                pixels.emplace_back(Get(indices[i], k));
        }
        return PixelArrayReference<Type>(pixels);
    }

    template<class Type>
    PixelArrayReference<Type> Matrix<Type>::operator()(const Vec2<uint32_t> p1, const Vec2<uint32_t> p2)
    {
        assert(p1[0] <= m_width && "First point x value should be within image bounds");
        assert(p1[1] <= m_height && "First point y value should be within image bounds");
        assert(p2[0] <= m_width && "Second point x value should be within image bounds");
        assert(p2[1] <= m_height && "Second point y value should be within image bounds");

        Vec2<uint32_t> rectSize = p2 - p1;

        auto pixels = std::vector<std::reference_wrapper<Type>>();
        pixels.reserve(rectSize[0] * rectSize[1] * m_channelNumber);
        for(uint32_t x = p1[0]; x < p2[0]; x++)
        {
            for(uint32_t y = p1[1]; y < p2[1]; y++)
            {
                for(uint8_t k = 0; k < m_channelNumber; k++)
                {
                    pixels.emplace_back(Get({x, y}, k));
                }
            }
        }
        return PixelArrayReference<Type>(pixels);
    }

    template<class Type>
    Type& Matrix<Type>::Get(uint32_t x, uint32_t y, uint8_t channel)
    {
        assert(x < m_width);
        assert(y < m_height);
        assert(channel < m_channelNumber);
        return m_data[(y * m_width * m_channelNumber) + (x * m_channelNumber) + channel];
    }

    template<class Type>
    Type Matrix<Type>::Get(uint32_t x, uint32_t y, uint8_t channel) const
    {
        assert(x < m_width);
        assert(y < m_height);
        assert(channel < m_channelNumber);
        return m_data[(y * m_width * m_channelNumber) + (x * m_channelNumber) + channel];
    }

    template<class Type>
    Type& Matrix<Type>::Get(const Vec2<uint32_t>& position, uint8_t channel)
    {
        assert(position[0] < m_width);
        assert(position[1] < m_height);
        assert(channel < m_channelNumber);
        return m_data[(position[1] * m_width * m_channelNumber) + (position[0] * m_channelNumber) + channel];
    }

    template<class Type>
    Type Matrix<Type>::Get(const Vec2<uint32_t>& position, uint8_t channel) const
    {
        assert(position[0] < m_width);
        assert(position[1] < m_height);
        assert(channel < m_channelNumber);
        return m_data[(position[1] * m_width * m_channelNumber) + (position[0] * m_channelNumber) + channel];
    }

    template<class Type>
    Type& Matrix<Type>::Get(const Vec3<uint32_t>& position)
    {
        assert(position.X() < m_width);
        assert(position.Y() < m_height);
        assert(position.Z() < m_channelNumber);
        return m_data[(position.X() * m_height + position.Y()) * m_channelNumber + position.Z()];
    }

    template<class Type>
    Type Matrix<Type>::Get(const Vec3<uint32_t>& position) const
    {
        assert(position.X() < m_width);
        assert(position.Y() < m_height);
        assert(position.Z() < m_channelNumber);
        return m_data[(position.X() * m_height + position.Y()) * m_channelNumber + position.Z()];
    }

    template<class Type>
    std::vector<Type>& Matrix<Type>::Data()
    {
        return m_data;
    }

    template<class Type>
    const std::vector<Type>& Matrix<Type>::Data() const
    {
        return m_data;
    }

    template<class Type>
    void Matrix<Type>::Set(const Vec2<uint32_t>& position, uint8_t k, const Type& t)
    {
        assert(position[0] < m_width);
        assert(position[1] < m_height);
        assert(k < m_channelNumber);
        m_data[(position[0] * m_height + position[1]) * m_channelNumber + k] = t;
    }


    template<class InputType, class ReturnType>
    Matrix<ReturnType> Transform(const Matrix<InputType>& img, std::function<ReturnType(const InputType&)> transformation)
    {
        const auto& oldData = img.Data();
        auto newData = std::vector<ReturnType>(oldData.size());
        for(std::size_t i = 0; i < oldData.size(); i++)
            newData[i] = transformation(oldData[i]);

        return Matrix<ReturnType>(newData, img.Width(), img.Height(), img.Channel());
    }

    template<class ImageType>
    PixelArrayReference<ImageType>::PixelArrayReference(const std::vector<std::reference_wrapper<ImageType>>& data) :
        m_data(data)
    {}

    template<class ImageType>
    PixelArrayReference<ImageType>& PixelArrayReference<ImageType>::operator*=(ImageType scalar)
    {
        for(auto& p : m_data)
            p.get() *= scalar;

        return *this;
    }

    template<class ImageType>
    PixelArrayReference<ImageType>& PixelArrayReference<ImageType>::operator/=(ImageType scalar)
    {
        for(auto& p : m_data)
            p.get() /= scalar;

        return *this;
    }

    template<class ImageType>
    PixelArrayReference<ImageType>& PixelArrayReference<ImageType>::operator+=(ImageType scalar)
    {
        for(auto& p : m_data)
            p.get() += scalar;
        return *this;
    }

    template<class ImageType>
    PixelArrayReference<ImageType>& PixelArrayReference<ImageType>::operator-=(ImageType scalar)
    {
        for(auto& p : m_data)
            p.get() -= scalar;
        return *this;
    }

    template<class ImageType>
    PixelArrayReference<ImageType>& PixelArrayReference<ImageType>::operator=(ImageType scalar)
    {
        for(auto& p : m_data)
            p.get() = scalar;
        return *this;
    }
}

