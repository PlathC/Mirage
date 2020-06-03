#include <Mirage/Mirage.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg", 4);

    Timer sobelTimer{}, cannyTimer{};

    sobelTimer.Start();
    Matrix<double> matSobel = Threshold(Sobel(mat));
    sobelTimer.Stop();

    cannyTimer.Start();
    Matrix<double> matCanny = Canny(Convolve(mat, mrg::gaussianBlurKernel5x5));
    cannyTimer.Stop();

    std::cout << "Sobel compute time : " << sobelTimer.Duration() << std::endl;
    std::cout << "Canny compute time : " << cannyTimer.Duration() << std::endl;

    ImageParser::ToFile(matSobel, "../examples/edgedetection/Results/HouseDublin-Sobel.jpg");
    ImageParser::ToFile(matCanny, "../examples/edgedetection/Results/HouseDublin-Canny.jpg");

    return EXIT_SUCCESS;
}