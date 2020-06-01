#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    QApplication app{argc, argv};

    Viewer viewer = Viewer([](mrg::Matrix<uint16_t> img) -> mrg::Matrix<uint16_t> {
        auto raw = img.Canny().Scale(400, 273, [](uint32_t x, uint32_t y, uint8_t k,
                                                  const std::vector<double>& oldData,
                                                  const typename mrg::Matrix<double>::ScalingSettings& settings) -> double
        {
            return mrg::ScalingNearestNeighbor(x, y, k, oldData, settings);
        });
        return mrg::Matrix<uint16_t>(raw.DataInType<uint16_t>(), raw.Width(), raw.Height(), 1);
    });
    viewer.show();

    return app.exec();
}