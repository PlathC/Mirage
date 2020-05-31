#include "Mirage/Viewer/Viewer.hpp"

#include <utility>
#include "ui_Viewer.h"

namespace mrg
{
    const mrg::Matrix<uchar> Viewer::whiteImage = mrg::Matrix<uchar>({ 255, 255, 255 }, 1, 1, 3);

    Viewer::Viewer(ImageModifier modifier, QWidget* parent):
            QMainWindow(parent),
            m_ui(new Ui::Viewer),
            m_modifier(std::move(modifier))
    {
        m_ui->setupUi(this);
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

    void Viewer::OpenImage()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Image"), "../samples", tr("Image Files (*.png *.jpg *.bmp)"));

        if(fileName.isEmpty())
            return;

        try
        {
            m_image = ImageParser::FromFile<uint16_t>(fileName.toStdString(), 3);
            if(m_modifier)
                m_image = m_modifier(m_image);

            DrawImage(m_ui->m_lblImage, m_image);
        }
        catch(std::exception& e)
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