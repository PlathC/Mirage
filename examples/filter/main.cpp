//
// Created by Cyprien Plateau--Holleville on 12/08/2019.
//

#include <Mirage/Mirage.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    Timer filterTimer{};

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/rubberwhale.png", 4);

    filterTimer.Start();
    Convolve(mat, mrg::averageKernel5x5);

    Scale<uint16_t>(mat, mat.Width() * 2, mat.Height() * 2,
            static_cast<mrg::ScalingFunction<uint16_t>>(&mrg::ScalingNearestNeighbor<uint16_t>)
            );

    filterTimer.Stop();

    std::cout << "Filter compute time : " << filterTimer.Duration() << std::endl;

    ImageParser::ToFile(mat, "../examples/filter/Results/rubberwhale-convolved.jpg");

    return EXIT_SUCCESS;
}