#include <iostream>
#include <vector>

#include "include/Core/Vec.h"
#include "include/Image/Matrix.h"
#include "include/Image/ImageParser.h"

int main()
{
    using namespace imp;

    Matrix<Vec4d> mat{};
    mat = ImageParser::FromFile<Vec4d>("../samples/engine.png", 4);

    Matrix<uint8_t> matConvoluted = mat.Sobel().Threshold<uint8_t>();

    ImageParser::ToFile(matConvoluted, "../samples/engine-sobel.png");

    return EXIT_SUCCESS;
}