<h1 align="center">Mirage</h1> 

An image processing library for learning purpose in C++17.

Build status (GCC/Linux) : [![Build Status](https://travis-ci.org/PlathC/Mirage.svg?branch=master)](https://travis-ci.org/PlathC/Mirage)

Code quality : [![Codacy Badge](https://api.codacy.com/project/badge/Grade/e7674eb14f3a4636b98ded41d9cbb42c)](https://www.codacy.com/manual/PlathC/Mirage?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=PlathC/Mirage&amp;utm_campaign=Badge_Grade)

<h2 align="center">The library</h2>

### __Tasks__

__Library features__

| Feature           | Progress                                                     |
|-------------------|--------------------------------------------------------------|
| Image structure   | Done                                                         |
| Parser            | Done (PNG/JPEG)                                              |
| Mirage Viewer     | In dev                                                       |

__Image processing features__ 

| Feature                          | Progress             |
|----------------------------------|----------------------|
| Image structure                  | Done                 |
| Bit depth                        | To do                |
| DFT                              | To do                |
| Filter                           | Done                 |
| Sobel / Threshold                | Done                 |
| Histogram Equalization           | Done                 |
| Adaptive Histogram Equalization  | To do                |
| Canny                            | Done                 |
| Crop / Scale                     | Done                 |
| Video support                    | To do                |
| Optimization (Realtime use)      | To do                |
| Test (Catch2)                    | To do                |

<h2 align="center">Build</h2>

### Dependencies 

*   LibPng
*   LibJpeg-turbo
*   Qt5
 
### Compiler

This project has been tested with MinGW and MSVC (VS2017).

<h2 align="center">Examples</h2>

#### __Filter__ 

One can use the Convolve function to filter an image with m_a kernel.

The following example show how to apply m_a Gaussian Blur to an image using 
m_a kernel provide in the library.

```cpp
#include <Mirage/Mirage.hpp>

int main()
{
    using namespace mrg;

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/rubberwhale.png", 4);
    Matrix<uint16_t> matConvolve = mat.Convolve(mrg::averageKernel5x5);

    auto scaled = matConvolve.Scale(matConvolve.Width() * 2., matConvolve.Height() * 2.,
                                    [](uint32_t x, uint32_t y, uint8_t k,
                                       const std::vector<uint16_t>& oldData,
                                       const Matrix<uint16_t>::ScalingSettings& settings) -> uint16_t
                                    {
                                        return mrg::ScalingNearestNeighbor(x, y, k, oldData, settings);
                                    });
    ImageParser::ToFile(scaled, "../examples/filter/Results/rubberwhale-convolved.jpg");

    return EXIT_SUCCESS;
}
```

###### Results 

![RubberWhale classic](readmefiles/rubberwhale.png) ![RubberWhale convolve](readmefiles/rubberwhale-convolve.png) 

#### __Edges detection__

The library provides Canny and Sobel algorithm which allow to extract 
contour lines within m_a given image.

```cpp
#include <Mirage/Mirage.hpp>

int main()
{
    using namespace mrg;

    Matrix<uint16_t> mat = ImageParser::FromFile<uint16_t>("../samples/HouseDublin.jpg", 4);

    Timer sobelTimer{}, cannyTimer{};

    sobelTimer.Start();
    Matrix<double> matSobel = mat.Sobel().Threshold<double>();
    sobelTimer.Stop();

    cannyTimer.Start();
    Matrix<double> matCanny = mat.Convolve(mrg::gaussianBlurKernel5x5).Canny();
    cannyTimer.Stop();

    std::cout << "Sobel compute time : " << sobelTimer.Duration() << std::endl;
    std::cout << "Canny compute time : " << cannyTimer.Duration() << std::endl;

    ImageParser::ToFile(matSobel, "../examples/edgedetection/Results/HouseDublin-Sobel.jpg");
    ImageParser::ToFile(matCanny, "../examples/edgedetection/Results/HouseDublin-Canny.jpg");

    return EXIT_SUCCESS;
}
```

###### Results

Original : 

![Dublin Classic](readmefiles/HouseDublin.jpg) 

Canny :

![Dublin Canny](readmefiles/HouseDublin-Canny.jpg)

Sobel :

![Dublin Canny](readmefiles/HouseDublin-Sobel.jpg) 

### Histogram Equalization

The library provide an histogram equalization function for grayscale and 
color image.

```cpp
#include <Mirage/Mirage.hpp>

int main()
{
    using namespace mrg;

    auto mat = ImageParser::FromFile<uint16_t>("../samples/lena.png", 4);
    Timer timer{};

    timer.Start();
    auto matEq = mat.HistogramEqualization();
    timer.Stop();

    std::cout << "Duration : " << timer.Duration() << std::endl;

    ImageParser::ToFile(matEq, "../examples/histeq/Results/lenaC-eq.png");

    return EXIT_SUCCESS;
}
```

###### Results 

![Lena Gray](readmefiles/lena-gray.jpg) ![Equalized Lena](readmefiles/lena-eq.jpg) 

![Lena Gray](samples/lena.png) ![Equalized Lena](readmefiles/lenaC-eq.png) 


### __Viewer__

A viewer is implemented in order to provide an easy way to test each features with a
 visualization tool.
```cpp
#include <QApplication>

#include <Mirage/Mirage.hpp>
#include <Mirage/Viewer/Viewer.hpp>

int main(int argc, char** argv)
{
    using namespace mrg;

    QApplication app{argc, argv};

    Viewer viewer = Viewer([](mrg::Matrix<uint16_t> img) -> mrg::Matrix<uint16_t> {
        auto raw = img.Canny().Scale(400, 273, [](uint32_t x, uint32_t y, uint8_t k,
                                                  const std::vector<double>& oldData,
                                                  const typename mrg::Matrix<double>::ScalingSettings& settings) -> double
        {
            return mrg::ScalingNearestNeighbor(x, y, k, oldData, settings);
        });
        return mrg::Matrix<uint16_t>(raw.DataInType<uint16_t>(), raw.Width(), raw.Height(), 1);
    });
    viewer.show();

    return app.exec();
}
}
```