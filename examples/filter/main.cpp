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
            [](uint32_t x, uint32_t y, uint8_t k,
                    const std::vector<uint16_t>& oldData,
                    const ScalingSettings& settings) -> uint16_t
                    {
                        return mrg::ScalingNearestNeighbor(x, y, k, oldData, settings);
                    }
            );

    filterTimer.Stop();

    std::cout << "Filter compute time : " << filterTimer.Duration() << std::endl;

    ImageParser::ToFile(mat, "../examples/filter/Results/rubberwhale-convolved.jpg");

    return EXIT_SUCCESS;
}