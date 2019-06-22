
namespace ImPro {

    template<typename Type>
    Matrix<Type>::Matrix() {}

    template<typename Type>
    Matrix<Type>::Matrix(const unsigned int width, const unsigned int height)
    {
        this->width = width;
        this->height = height;
        this->data.resize(width * height);
    }

    template<typename Type>
    Matrix<Type>::Matrix(std::vector<Type> pixels, const unsigned int width, const unsigned int height)
    {
        this->width = width;
        this->height = height;
        this->data = pixels;
    }

    template<typename Type>
    Type& Matrix<Type>::Get(unsigned int w, unsigned int h)
    {
        assert(w < width  && h < height);
        return this->data[w * width + h];
    }

    template<typename Type>
    std::vector<Type> Matrix<Type>::GetData()
    {
        return this->data;
    }

    template<typename Type>
    void Matrix<Type>::Set(unsigned int w, unsigned int h, const Type& t)
    {
        this->data[w * width + h] = t;
    }
}