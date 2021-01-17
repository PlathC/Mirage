#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

int main(int argc, char** argv)
{
    QApplication app{argc, argv};

    mrg::Viewer viewer = mrg::Viewer([](const mrg::Matrix<uint16_t>& img) -> mrg::Matrix<uint16_t>
        {
            auto raw = mrg::FFT2(mrg::ToGrayScale<uint16_t, float>(img));
            raw = mrg::FFT2(raw, true);
            return mrg::Transform<std::complex<float>, uint16_t>(raw, [](const std::complex<float>& p) -> uint16_t
            {
                return static_cast<uint16_t>(p.real());
            });
        }
    );
    viewer.show();

    return app.exec();
}