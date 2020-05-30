
namespace mrg
{
    template<class T>
    void DrawImage(QLabel* lbl, const Matrix<T>& image)
    {
        std::vector<uchar> imgData = image.template GetRawData<uchar>();
        uint8_t channel = image.Channel();

        QImage::Format channelFormat;
        switch(channel)
        {
            case 1: channelFormat = QImage::Format_Grayscale8; break;
            default: channelFormat = QImage::Format_RGB888; break;
        }

        QImage tmp(imgData.data(), image.Width(), image.Height(), channelFormat);
        lbl->setScaledContents(true);
        lbl->setPixmap(QPixmap::fromImage(tmp));
    }
}