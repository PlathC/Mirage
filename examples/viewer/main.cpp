#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

template<class T>
mrg::Matrix<T> FloydSteinberg(const mrg::Matrix<T>& input)
{
    // Based on https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering
    assert(input.Channel() == 1 && "Floyd-Steinberg algorithm works only on grayscale images.");
    const auto closestColor = [](T pixel) {
        if(pixel < 64)
            return 0;
        else if(pixel >= 64 && pixel < 128)
            return 64;
        else if(pixel >= 128 && pixel < 192)
            return 128;
        else if(pixel >= 192 && pixel < 255)
            return 192;
    };

    auto result = mrg::Matrix<T>(input);
    for(uint32_t j = 1; j < input.Height() - 1; j++)
    {
        for(uint32_t i = 1; i < input.Width() - 1; i++)
        {
            auto oldValue = input.Get(i, j);
            auto newValue = closestColor(oldValue);
            result.Get(i, j) = newValue;
            int32_t quantificationError = oldValue - newValue;
            result.Get(i + 1, j)        += quantificationError * 7. / 16.;
            result.Get(i - 1, j + 1) += quantificationError * 3. / 16.;
            result.Get(i, j + 1)        += quantificationError * 5. / 16.;
            result.Get(i + 1, j + 1) += quantificationError * 1. / 16.;
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    QApplication app{argc, argv};

    mrg::Viewer viewer = mrg::Viewer([](const mrg::Matrix<uint16_t>& img) -> mrg::Matrix<uint16_t>
        {
            auto temp = mrg::Matrix<uint16_t>(img);
            if(temp.Channel() > 1)
                temp = mrg::ToGrayScale<uint16_t, uint16_t>(temp);

            return FloydSteinberg(temp);
        }
    );
    viewer.show();

    return app.exec();
}