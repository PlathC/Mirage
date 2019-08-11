# Mirage

An image processing library for learning purpose in C++17.

## The library 

### __Tasks__

| Feature | Progress |
|---------|----------|
| Image structure | Done |
| Parser | Done (PNG) |
| Filter | To do |
| Sobel / Threshold | Done |
| Canny | To do |
| Viewer | In Progress (Vec4ui image only and distortion of the image.) |

###  __Examples__

#### __Sobel__

A Sobel filter is directly implemented in the library and can be used as :

```cpp
#include "Mirage/Mirage.hpp"

int main()
{
    using namespace mrg;

    Matrix<Vec4d> mat{};
    mat = ImageParser::FromFile<Vec4d>("../../../samples/lena.png", 4);

    Matrix<double> matConvoluted = mat.Sobel();

    ImageParser::ToFile(matConvoluted, "../Results/lena-convolve.png");

    return EXIT_SUCCESS;
}
```

__Result :__ 

![Lena Classic](samples/lena.png) ![Lena Sobel](readmefiles/lena-sobel.jpg) 

### __Viewer__

The viewer can be used as follow :

```cpp
#include <Mirage/Mirage.hpp>

int main()
{
    using namespace mrg;

    Viewer viewer = Viewer(800,800, ImageParser::FromFile<Vec4ui8>("../samples/lena.png", 4));
    try{
        viewer.Show();
    }catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

__Result :__

![Lena Viewer](readmefiles/viewer.jpg)

## Build

### Dependencies 
    
- LibPng (Read Png Images)
- Vulkan (Image viewer)
- GLM
- GLFW3
 
### CMake

This project needs CMake to be built. 

### Compiler

This project has been tested with MinGW and MSVC (VS2017).