#ifndef MIRAGE_VIEWER
#define MIRAGE_VIEWER

#include <QMainWindow>

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

        ~Viewer() override;
    private:
        Ui::Viewer* m_ui;
    };
}

#endif // MIRAGE_VIE    WER