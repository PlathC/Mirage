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
        void DrawImage();

        ~Viewer() override;
    private:
        Ui::Viewer* m_ui;
        mrg::Matrix<uint16_t> m_image;
        mrg::Matrix<uchar> m_displayedImage;
        QImage m_qImage;
        ImageModifier m_modifier;

        static const mrg::Matrix<uint16_t> whiteImage;
    };
}

#endif // MIRAGE_VIEWER