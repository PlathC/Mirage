#include "Mirage/Viewer/Viewer.hpp"
#include "ui_Viewer.h"

namespace mrg
{
    const mrg::Matrix<uchar> Viewer::whiteImage = mrg::Matrix<uchar>({ 255, 255, 255 }, 1, 1, 3);

    Viewer::Viewer(QWidget* parent):
            QMainWindow(parent),
            m_ui(new Ui::Viewer)
    {
        m_ui->setupUi(this);
        DrawImage(m_ui->m_lblImage, whiteImage);

        QObject::connect(m_ui->m_pbOpen, &QPushButton::pressed, [&]()
        {
            OpenImage();
        });
    }

    void Viewer::OpenImage()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Image"), "../samples", tr("Image Files (*.png *.jpg *.bmp)"));

        if(fileName.isEmpty())
            return;

        try
        {
            m_image = ImageParser::FromFile<uchar>(fileName.toStdString(), 3);
            DrawImage(m_ui->m_lblImage, m_image);
        }
        catch(std::exception& e)
        {
            QMessageBox::warning(this, "Parsing error", e.what());
            return;
        }
    }

    Viewer::~Viewer()
    {
        delete m_ui;
    }
}