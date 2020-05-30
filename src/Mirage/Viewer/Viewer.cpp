#include "Mirage/Viewer/Viewer.hpp"
#include "ui_Viewer.h"

namespace mrg
{
    Viewer::Viewer(QWidget* parent):
            QMainWindow(parent),
            m_ui(new Ui::Viewer)
    {
        m_ui->setupUi(this);
    }

    Viewer::~Viewer()
    {
        delete m_ui;
    }
}