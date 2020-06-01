//
// Created by Cyprien Plateau--Holleville on 12/08/2019.
//

#include <Mirage/Mirage.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/rubberwhale.png", 4);
    Matrix<uint16_t> matConvolve = mat.Convolve(mrg::averageKernel5x5);

    auto scaled = matConvolve.Scale(matConvolve.Width() * 2., matConvolve.Height() * 2.,
                                    [](uint32_t x, uint32_t y, uint8_t k,
                                       const std::vector<uint16_t>& oldData,
                                       const Matrix<uint16_t>::ScalingSettings& settings) -> uint16_t
                                    {
                                        return mrg::ScalingNearestNeighbor(x, y, k, oldData, settings);
                                    });
    ImageParser::ToFile(scaled, "../examples/filter/Results/rubberwhale-convolved.jpg");

    return EXIT_SUCCESS;
}