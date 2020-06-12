#include <Mirage/Mirage.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg", 4);

    Timer sobelTimer{}, cannyTimer{};

    sobelTimer.Start();
    auto matSobel = Sobel(mat);
    Threshold(matSobel);
    sobelTimer.Stop();

    cannyTimer.Start();
    Convolve(mat, mrg::gaussianBlurKernel5x5);
    Matrix<double> matCanny = Canny(mat);
    cannyTimer.Stop();

    std::cout << "Sobel compute time : " << sobelTimer.Duration() << std::endl;
    std::cout << "Canny compute time : " << cannyTimer.Duration() << std::endl;

    ImageParser::ToFile(matSobel, "../examples/edgedetection/Results/HouseDublin-Sobel.jpg");
    ImageParser::ToFile(matCanny, "../examples/edgedetection/Results/HouseDublin-Canny.jpg");

    return EXIT_SUCCESS;
}