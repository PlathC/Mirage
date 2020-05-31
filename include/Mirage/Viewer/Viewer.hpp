#ifndef MIRAGE_VIEWER
#define MIRAGE_VIEWER

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>

#include "Mirage/Image/ImageParser.hpp"

namespace Ui
{
    class Viewer;
}

namespace mrg
{
    class Viewer : public QMainWindow
    {
    Q_OBJECT
    public:
        explicit Viewer(QWidget* parent = nullptr);

        void OpenImage();
        void SaveImage();

        ~Viewer() override;
    private:
        Ui::Viewer* m_ui;
        mrg::Matrix<uchar> m_image;

        static const mrg::Matrix<uchar> whiteImage;
    };

    template<class T>
    void DrawImage(QLabel* lbl, const Matrix<T>& image);
}

#include "Mirage/Viewer/Viewer.inl"

#endif // MIRAGE_VIE    WER