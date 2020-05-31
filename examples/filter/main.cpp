//
// Created by Cyprien Plateau--Holleville on 12/08/2019.
//

#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg", 4);
    Matrix<uint16_t> matConvolve = mat.Convolve(mrg::averageKernel5x5);
    ImageParser::ToFile(matConvolve, "../examples/filter/Results/HouseDublin-convolved.jpg");

    return EXIT_SUCCESS;
}