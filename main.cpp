#include <iostream>
#include <vector>

#include "include/Core/Vec.hpp"
#include "include/Image/Matrix.hpp"
#include "include/Image/ImageParser.hpp"

int main()
{
    using namespace imp;

    Matrix<Vec4d> mat{};
    mat = ImageParser::FromFile<Vec4d>("../samples/engine.png", 4);

    Matrix<Vec4d> matConvoluted = mat.Convolve(imp::gaussianBlurKernel3x3);//ToGrayScale<double>().Convolve(kernel);

    ImageParser::ToFile(matConvoluted, "../samples/engine-convolve.png");

    return EXIT_SUCCESS;
}