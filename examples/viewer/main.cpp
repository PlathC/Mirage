#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    QApplication app{argc, argv};

    Viewer viewer = Viewer([](mrg::Matrix<uint16_t> img) -> mrg::Matrix<uint16_t> {
        auto raw = img.Canny().DataInType<uint16_t>();
        return mrg::Matrix<uint16_t>(raw, img.Width(), img.Height(), 1);
    });
    viewer.show();

    return app.exec();
}