#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    QApplication app{argc, argv};
    Viewer viewer;
    viewer.show();

    return app.exec();
}