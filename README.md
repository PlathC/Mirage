![Logo](readmefiles/banniere.png) 

An image processing library for learning purpose in C++17.

[![Build Status](https://travis-ci.org/PlathC/Mirage.svg?branch=master)](https://travis-ci.org/PlathC/Mirage)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e7674eb14f3a4636b98ded41d9cbb42c)](https://www.codacy.com/manual/PlathC/Mirage?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=PlathC/Mirage&amp;utm_campaign=Badge_Grade) 
[![Coverage Status](https://coveralls.io/repos/github/PlathC/Mirage/badge.svg?branch=master)](https://coveralls.io/github/PlathC/Mirage?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

<h2 align="center">The library</h2>

### __Tasks__

__Library features__

| Feature           | Progress                                                     |
|-------------------|--------------------------------------------------------------|
| Image structure   | Done                                                         |
| Parser            | Done (PNG/JPEG)                                              |
| Mirage Viewer     | In progress                                                  |

__Image processing features__ 

| Feature                                    | Progress             |
|--------------------------------------------|----------------------|
| Image structure                            | Done                 |
| Filter (convolution)                       | Done                 |
| Sobel / Threshold                          | Done                 |
| Histogram Equalization                     | Done                 |
| Canny                                      | Done                 |
| Crop / Scale                               | Done                 |
| Matrix transform                           | In progress          |
| DFT                                        | Done                 |
| FFT                                        | Done                 |
| Mask operations                            | To do                |
| Bit depth / Pixel type                     | To do                |
| Adaptive Histogram Equalization            | To do                |
| Floyd-Steinberg                            | To do                |
| Video support                              | To do                |
| Optimization (Realtime use, GPU - MT)      | To do                |

<h2 align="center">Build</h2>

### Dependencies 

| Feature                          | Dependencies |
|----------------------------------|--------------|
| Mirage + example                 | None         | 
| MIRAGE_BUILD_VIEWER              | QT5          | 
 
### Compiler

This project has been tested with MSVC (VS2019).

<h2 align="center">Examples</h2>

#### __Filter__ 

One can use the Convolve function to filter an image with a kernel.

The following example show how to apply a Gaussian Blur to an image using 
a kernel provide in the library.

##### Filter Results 

<p align="center">
	<img src="readmefiles/rubberwhale.png" alt="RubberWhale classic"/> <img src="readmefiles/rubberwhale-convolve.png" alt="RubberWhale convolved"/> 
</p>

#### __Edges detection__

The library provides Canny and Sobel algorithm which allow to extract 
contour lines within m_a given image.

##### Edges detection Results

Original : 

<p align="center">
	<img src="readmefiles/HouseDublin.jpg" alt="Dublin Classic"/> 
</p>

Canny :

<p align="center">
	<img src="readmefiles/HouseDublin-Canny.jpg" alt="Dublin Canny"/> 
</p>

Sobel :

<p align="center">
	<img src="readmefiles/HouseDublin-Sobel.jpg" alt="Dublin Canny"/> 
</p>

#### __Histogram Equalization__

The library provide an histogram equalization function for grayscale and 
color image.

##### Histogram Equalization Results 

<p align="center">
	<img src="readmefiles/lena-gray.jpg" alt="Lena Gray"/> <img src="readmefiles/lena-eq.jpg" alt="Equalized Lena"/>
</p>


<p align="center">
	<img src="samples/lena.png" alt="Lena Gray"/> <img src="readmefiles/lenaC-eq.png" alt="Equalized Lena"/>
</p>

### __Fourier transform__

DFT and FFT 2D algorithms are implemented and provide the ability to work directly 
in the frequency domain.

<p align="center">
	<img src="readmefiles/lena-gray.jpg" alt="Lena Gray"/> <img src="readmefiles/lena-fft.jpg" alt="Lena Gray"/>
</p>

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
