#include <Mirage/Mirage.hpp>
#include <iostream>
int main(int argc, char** argv)
{
    using namespace mrg;

    try 
    {
        Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg");

        Timer sobelTimer{}, cannyTimer{};

        sobelTimer.Start();
        auto matSobel = Sobel(mat);
        Otsu(matSobel);
        sobelTimer.Stop();

        cannyTimer.Start();
        Matrix<double> matCanny = Canny(mat);
        cannyTimer.Stop();

        std::cout << "Sobel compute time : " << sobelTimer.Duration() << std::endl;
        std::cout << "Canny compute time : " << cannyTimer.Duration() << std::endl;

        ImageParser::ToFile(matSobel, "./HouseDublin-Sobel.jpg");
        ImageParser::ToFile(matCanny, "./HouseDublin-Canny.jpg");
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}