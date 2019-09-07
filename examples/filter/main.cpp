//
// Created by Cyprien Plateau--Holleville on 12/08/2019.
//

#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<Vec4d> mat = ImageParser::FromFile<Vec4d>("../samples/HouseDublin.jpg", 4);
    Matrix<Vec4d> matConvolve = mat.Convolve(mrg::averageKernel5x5);
    ImageParser::ToFile(matConvolve, "../examples/filter/Results/HouseDublin-convolved.jpg");

    return EXIT_SUCCESS;
}