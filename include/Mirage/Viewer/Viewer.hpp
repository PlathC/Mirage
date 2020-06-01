#ifndef MIRAGE_VIEWER
#define MIRAGE_VIEWER

#include <functional>

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
        using ImageModifier = std::function<mrg::Matrix<uint16_t>(const mrg::Matrix<uint16_t>&)>;

    public:
        explicit Viewer(ImageModifier modifier = ImageModifier(), QWidget* parent = nullptr);

        void resizeEvent(QResizeEvent* event) override;

        void OpenImage();
        void SaveImage();

        ~Viewer() override;
    private:
        Ui::Viewer* m_ui;
        mrg::Matrix<uint16_t> m_image;
        ImageModifier m_modifier;

        static const mrg::Matrix<uchar> whiteImage;
    };

    template<class T>
    void DrawImage(QLabel* lbl, const Matrix<T>& image);
}

#include "Mirage/Viewer/Viewer.inl"

#endif // MIRAGE_VIE    WER