//
// Created by Cyprien Plateau--Holleville on 12/08/2019.
//

#include <Mirage/Mirage.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    Timer filterTimer{};

    try
    {
        Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/rubberwhale.png");

        filterTimer.Start();
        //mat = Convolve(mat, mrg::averageKernel5x5);
        mat = Convolve<uint16_t>(mat, &mrg::KernelMax<uint16_t>, 17);

        Scale<uint16_t>(mat, mat.Width() * 2, mat.Height() * 2,
                        static_cast<mrg::ScalingFunction<uint16_t>>(&mrg::ScalingNearestNeighbor<uint16_t>)
        );

        filterTimer.Stop();
        std::cout << "Filter compute time : " << filterTimer.Duration() << std::endl;
        ImageParser::ToFile(mat, "./rubberwhale-convolved.jpg");

        Matrix<float> original = ToGrayScale<uint16_t, float>(ImageParser::FromFile<uint16_t>("../samples/lena.png"));

        Timer dftTimer{};
        dftTimer.Start();

        // Discrete Fourier Transform
        std::cout << "Compute DFT" << std::endl;
        auto dftImage = mrg::FFT2(original);


        ImageParser::ToFile(mrg::Transform<std::complex<float>, float>(dftImage, [](const std::complex<float>& p) -> float
        {
            return std::log(std::sqrt(p.real() * p.real() + p.imag() * p.imag())) * 10;
        }), "./dftResult.jpg");

        dftTimer.Stop();
        std::cout << "DFT took " << dftTimer.Duration() << std::endl;

        // IDFT
        Timer invDftTimer{};
        invDftTimer.Start();
        std::cout << "Compute inverse DFT" << std::endl;

        auto invDftImage = mrg::FFT2(dftImage, true);

        ImageParser::ToFile(mrg::Transform<std::complex<float>, float>(invDftImage, [](const std::complex<float>& p) -> float
        {
            return p.real();
        }), "./invDftResult.jpg");

        invDftTimer.Stop();

        std::cout << "Inv DFT took " << dftTimer.Duration() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}