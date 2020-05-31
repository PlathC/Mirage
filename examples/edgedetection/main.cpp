#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg", 4);

    Timer sobelTimer{}, cannyTimer{};

    sobelTimer.Start();
    Matrix<double> matSobel = mat.Sobel().Threshold<double>();
    sobelTimer.Stop();

    cannyTimer.Start();
    Matrix<double> matCanny = mat.Convolve(mrg::gaussianBlurKernel5x5).Canny();
    cannyTimer.Stop();

    std::cout << "Sobel compute time : " << sobelTimer.Duration() << std::endl;
    std::cout << "Canny compute time : " << cannyTimer.Duration() << std::endl;

    ImageParser::ToFile(matSobel, "../examples/edgedetection/Results/HouseDublin-Sobel.jpg");
    ImageParser::ToFile(matCanny, "../examples/edgedetection/Results/HouseDublin-Canny.jpg");

    return EXIT_SUCCESS;
}