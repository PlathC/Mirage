//
// Created by Cyprien Plateau--Holleville on 14/08/2019.
//

#include <Mirage/Mirage.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    try
    {
        auto mat = ImageParser::FromFile<uint16_t>("../samples/lena.png");
        mat = Crop(mat, {mat.Width() / 2  , mat.Height() / 2},
                   {mat.Width(), mat.Height()});
        Timer timer{};

        timer.Start();
        HistogramEqualization(mat);
        timer.Stop();

        std::cout << "Duration : " << timer.Duration() << std::endl;

        ImageParser::ToFile(mat, "./lenaC-eq.png");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}