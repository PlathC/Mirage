# Mirage

An image processing library for learning purpose in C++17.

## The library 

### __Tasks__

| Feature | Progress |
|---------|----------|
| Image structure | In progress |
| Parser (Using LibPng...) | In progress |
| Filter | To do |
| Sobel | In progress |
| Canny | To do |
| Viewer | To do |

###  __Examples__

#### __Sobel__

Sobel filter is directly implemented in the library and can be used as :

```cpp
#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<Vec4d> mat{};
    mat = ImageParser::FromFile<Vec4d>("../samples/lena.png", 4);

    Matrix<Vec4d> matConvoluted = mat.Convolve(mrg::gaussianBlurKernel3x3);
    
    ImageParser::ToFile(matConvoluted, "../samples/lena-convolve.png");

    return EXIT_SUCCESS;
}
```

__Result :__ 

![Lena Classic](samples/lena.png) ![Lena Sobel](readmefiles/lena-sobel.jpg) 

## Build

This project use LibPNG to read png images. 
It has to be generated with CMake.

Build has been test on Windows with Mingw.