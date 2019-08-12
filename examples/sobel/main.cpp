#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<Vec4d> mat = ImageParser::FromFile<Vec4d>("../samples/rubberwhale.png", 4);

    Matrix<double> matSobel = mat.Sobel().Threshold<double>();

    ImageParser::ToFile(matSobel, "../examples/sobel/Results/rubberwhale.png");

    return EXIT_SUCCESS;
}