namespace ImPro {

    template<typename Type>
    Matrix<Type>::Matrix() {}

    template<typename Type>
    ImPro::Matrix<Type>::Matrix(const unsigned int width, const unsigned int height)
    {
        this->width = width;
        this->height = height;
        this->data.resize(width * height);
    }

    template<typename Type>
    ImPro::Matrix<Type>::Matrix(std::string filename)
    {
        // @TODO : Implement file read to create image
        throw std::logic_error("This feature is not yet implemented.");
    }

    template<typename Type>
    ImPro::Matrix<Type>::Matrix(std::vector<Type> pixels, const unsigned int width, const unsigned int height)
    {
        this->width = width;
        this->height = height;
        this->data = pixels;
    }

    template<typename Type>
    Type& ImPro::Matrix<Type>::Get(unsigned int w, unsigned int h)
    {
        assert(w < width  && h < height);
        return this->data[w * width + h];
    }

    template<typename Type>
    void ImPro::Matrix<Type>::Set(unsigned int w, unsigned int h, const Type t)
    {
        this->data[w * width + h] = t;
    }
}