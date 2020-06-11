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
    m_data(pixels)
    {
    }

    template<class Type>
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
    Type Matrix<Type>::Get(uint32_t w, uint32_t h, uint8_t channel) const
    {
        assert(w < m_width);
        assert(h < m_height);
        assert(channel < m_channelNumber);
        return m_data[(w * m_height + h) * m_channelNumber + channel];
    }

    template<class Type>
    Type& Matrix<Type>::Get(uint32_t w, uint32_t h, uint8_t channel)
    {
        assert(w < m_width);
        assert(h < m_height);
        assert(channel < m_channelNumber);
        return m_data[(w * m_height + h) * m_channelNumber + channel];
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
    template<class ReturnType>
    std::vector<ReturnType> Matrix<Type>::DataInType() const
    {
        static_assert(std::is_arithmetic<ReturnType>::value, "The returning type must be a scalar");
        std::vector<ReturnType> rawData = std::vector<ReturnType>(m_width * m_height * m_channelNumber);

        for(uint32_t x = 0; x < m_width; x++)
        {
            for(uint32_t y = 0; y < m_height; y++)
            {
                for(uint32_t k = 0; k < m_channelNumber; k++)
                {
                    rawData[(x * m_height + y) * m_channelNumber + k] =
                            static_cast<ReturnType>(m_data[(x * m_height + y) * m_channelNumber + k]);
                }
            }
        }
        return rawData;
    }

    template<class Type>
    void Matrix<Type>::Set(uint32_t w, uint32_t h, uint8_t k, const Type& t)
    {
        assert(w < m_width);
        assert(h < m_height);
        assert(k < m_channelNumber);
        m_data[(w * m_height + h) * m_channelNumber + k] = t;
    }

}

