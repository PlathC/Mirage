#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

int main(int argc, char** argv)
{
    QApplication app{argc, argv};

    mrg::Viewer viewer = mrg::Viewer([](const mrg::Matrix<uint16_t>& img) -> mrg::Matrix<uint16_t>
        {
            auto temp = mrg::Matrix<uint16_t>(img);
            auto canny = mrg::Canny(temp);
            temp[canny == 255] = 255;

            temp({temp.Width() / 4, temp.Height() / 4},
                    { temp.Width() / 2 + temp.Width() / 4, temp.Height() / 2 + temp.Width() / 4}) = 0;

            mrg::ImageParser::ToFile(temp, "./test.png");
            return temp;
        }
    );
    viewer.show();

    return app.exec();
}