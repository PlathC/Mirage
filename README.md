# ImPro

An image processing library for learning purpose in C++17.

## Image 

1. __Tasks__

| Feature | Progress |
|---------|----------|
| Image structure | In progress |
| Parser (Using LibPng...) | In progress |
| Filter | To do |
| Sobel | In progress |
| Viewer | To do |

2. __Examples__

    a. __Sobel__

Sobel filter is directly implemented in the library and can be used as :

```cpp
    Matrix<Vec4d> mat = ImageParser::FromFile<Vec4d>("../samples/lena.png", 4);

    Matrix<uint8_t> matConvoluted = mat.Sobel().Threshold<uint8_t>();

    ImageParser::ToFile(matConvoluted, "../samples/lena-sobel.png");
```

__Result :__ 

![Lena Classic](samples/lena.png) ![Lena Sobel](readmefiles/lena-sobel.jpg) 

## Dependencies

1. __LibPNG__

This project use LibPNG to png read images. You can build for 
UNIX, or pre-built binaries can be found.
  