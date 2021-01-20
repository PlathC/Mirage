#include "Mirage/Viewer/Viewer.hpp"

#include <utility>

#include "ui_Viewer.h"

namespace mrg
{
    const mrg::Matrix<uint16_t> Viewer::whiteImage = mrg::Matrix<uint16_t>({ 57, 62, 70 }, 1, 1, 3);

    Viewer::Viewer(const ImageModifier modifier, QWidget* parent):
            QMainWindow(parent),
            m_ui(new Ui::Viewer),
            m_modifier(std::move(modifier))
    {
        m_ui->setupUi(this);
        m_ui->m_lblImage->setMinimumSize(1,1);

        m_image = whiteImage;
        DrawImage();

        QObject::connect(m_ui->m_pbOpen, &QPushButton::pressed, [&]()
        {
            OpenImage();
        });

        QObject::connect(m_ui->m_pbSave, &QPushButton::pressed, [&]()
        {
            SaveImage();
        });
    }

    void Viewer::resizeEvent(QResizeEvent* event)
    {
        QMainWindow::resizeEvent(event);
    }

    void Viewer::OpenImage()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Image"), "../samples", tr("Image Files (*.png *.jpg *.bmp)"));

        if(fileName.isEmpty())
            return;

        try
        {
            m_image = ImageParser::FromFile<uint16_t>(fileName.toStdString());
            if(m_modifier)
                m_image = m_modifier(m_image);

            DrawImage();
        }
        catch(const std::exception& e)
        {
            QMessageBox::warning(this, "Parsing error", e.what());
            return;
        }
    }

    void Viewer::SaveImage()
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "",
                                                        tr("Images (*.png *.xpm *.jpg)"));
        ImageParser::ToFile(m_image, fileName.toStdString());
    }

    void Viewer::DrawImage()
    {
        m_displayedImage = mrg::Transform<uint16_t, uchar>(m_image, [](const uint16_t & p) -> uchar {
            return static_cast<uchar>(p);
        });
        uint8_t channel = m_image.Channel();
        QImage::Format channelFormat;
        switch(channel)
        {
            case 1: channelFormat = QImage::Format_Grayscale8; break;
            case 3: channelFormat = QImage::Format_RGB888; break;
            default: channelFormat = QImage::Format_RGBA8888; break;
        }

        m_qImage = QImage(m_displayedImage.Data().data(), m_displayedImage.Width(), m_displayedImage.Height(),
                          static_cast<int>(m_displayedImage.Width() * m_displayedImage.Channel()), channelFormat);
        m_qImage.save("test.png");
        m_ui->m_lblImage->setScaledContents(true);
        auto img = QPixmap::fromImage(m_qImage);
        m_ui->m_lblImage->setPixmap(img);
    }

    Viewer::~Viewer()
    {
        delete m_ui;
    }
}