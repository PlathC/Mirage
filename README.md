![Logo](readmefiles/banniere.png) 

An image processing library for learning purpose in C++17.

[![Build Status](https://travis-ci.org/PlathC/Mirage.svg?branch=master)](https://travis-ci.org/PlathC/Mirage)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e7674eb14f3a4636b98ded41d9cbb42c)](https://www.codacy.com/manual/PlathC/Mirage?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=PlathC/Mirage&amp;utm_campaign=Badge_Grade) 
[![Coverage Status](https://coveralls.io/repos/github/PlathC/Mirage/badge.svg?branch=master)](https://coveralls.io/github/PlathC/Mirage?branch=master)

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
| Filter                           | Done                 |
| Sobel / Threshold                | Done                 |
| Histogram Equalization           | Done                 |
| Canny                            | Done                 |
| Crop / Scale                     | Done                 |
| Matrix transform                 | To do                |
| Bit depth / Pixel type           | To do                |
| DFT                              | To do                |
| Adaptive Histogram Equalization  | To do                |
| Floyd-Steinberg                  | To do                |
| Video support                    | To do                |
| Optimization (Realtime use)      | To do                |

<h2 align="center">Build</h2>

### Dependencies 

| Feature                          | Dependencies |
|----------------------------------|--------------|
| Mirage + example                 |None          | 
| MIRAGE_BUILD_VIEWER              |QT5           | 
 
### Compiler

This project has been tested with MinGW and MSVC (VS2017).

<h2 align="center">Examples</h2>

#### __Filter__ 

One can use the Convolve function to filter an image with a kernel.

The following example show how to apply a Gaussian Blur to an image using 
a kernel provide in the library.

##### Filter Results 

![RubberWhale classic](readmefiles/rubberwhale.png) ![RubberWhale convolve](readmefiles/rubberwhale-convolve.png) 

#### __Edges detection__

The library provides Canny and Sobel algorithm which allow to extract 
contour lines within m_a given image.

##### Edges detection Results

Original : 

![Dublin Classic](readmefiles/HouseDublin.jpg) 

Canny :

![Dublin Canny](readmefiles/HouseDublin-Canny.jpg)

Sobel :

![Dublin Canny](readmefiles/HouseDublin-Sobel.jpg) 

#### __Histogram Equalization__

The library provide an histogram equalization function for grayscale and 
color image.

##### Histogram Equalization Results 

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
    QApplication app{argc, argv};

    mrg::Viewer viewer = mrg::Viewer([](mrg::Matrix<uint16_t> img) -> mrg::Matrix<uint16_t>
        {
            auto raw = mrg::Canny(img);
            return mrg::Matrix<uint16_t>(raw.DataInType<uint16_t>(), raw.Width(), raw.Height(), 1);
        }
    );
    viewer.show();

    return app.exec();
}
```
