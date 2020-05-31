//
// Created by Cyprien Plateau--Holleville on 14/08/2019.
//

#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    auto mat = ImageParser::FromFile<uint16_t>("../samples/lena.png", 4);
    Timer timer{};

    timer.Start();
    auto matEq = mat.HistogramEqualization();
    timer.Stop();

    std::cout << "Duration : " << timer.Duration() << std::endl;

    ImageParser::ToFile(matEq, "../examples/histeq/Results/lenaC-eq.png");

    return EXIT_SUCCESS;
}