#include "Mirage/Viewer/Viewer.hpp"

#include <utility>
#include "ui_Viewer.h"

namespace mrg
{
    const mrg::Matrix<uchar> Viewer::whiteImage = mrg::Matrix<uchar>({ 57, 62, 70 }, 1, 1, 3);

    Viewer::Viewer(const ImageModifier modifier, QWidget* parent):
            QMainWindow(parent),
            m_ui(new Ui::Viewer),
            m_modifier(std::move(modifier))
    {
        m_ui->setupUi(this);
        m_ui->m_lblImage->setMinimumSize(1,1);

        DrawImage(m_ui->m_lblImage, whiteImage);

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

            DrawImage(m_ui->m_lblImage, m_image);
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

    Viewer::~Viewer()
    {
        delete m_ui;
    }
}