//
// Created by Cyprien Plateau--Holleville on 12/08/2019.
//

#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<Vec4d> mat = ImageParser::FromFile<Vec4d>("../samples/HouseDublin.jpg", 4);
    //Matrix<Vec4d> matConvolve = mat.Convolve(mrg::gaussianBlurKernel5x5);
    ImageParser::ToFile(mat, "../examples/filter/Results/HouseDublin.jpg");

    return EXIT_SUCCESS;
}