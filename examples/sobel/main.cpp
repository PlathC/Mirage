#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<Vec4d> mat{};
    mat = ImageParser::FromFile<Vec4d>("../samples/rubberwhale.png", 4);

    Matrix<double> matConvoluted = mat.Sobel().Threshold<double>();

    ImageParser::ToFile(matConvoluted, "../examples/sobel/Results/rubberwhale.png");

    return EXIT_SUCCESS;
}