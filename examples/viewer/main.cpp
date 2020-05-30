#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

int main(int argc, char** argv)
{
    QApplication app{argc, argv};

    using namespace mrg;
    Matrix<Vec4ui8> mat = ImageParser::FromFile<Vec4ui8>("../samples/tiled4x3.png", 4);
    Viewer viewer;

    viewer.show();

    return app.exec();
}