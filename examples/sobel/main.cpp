#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<Vec4d> mat{};
    mat = ImageParser::FromFile<Vec4d>("../../../samples/lena.png", 4);

    Matrix<double> matConvoluted = mat.Sobel();//ToGrayScale<double>().Convolve(kernel);

    ImageParser::ToFile(matConvoluted, "../Results/lena-convolve.png");

    return EXIT_SUCCESS;
}