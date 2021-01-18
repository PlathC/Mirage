# Mirage Features

#### __Filter__ 

One can use the Convolve function to filter an image with a kernel.

The following example show how to apply a Gaussian Blur to an image using 
a kernel provide in the library.

##### Filter Results 

<p align="center">
	<img src="readmefiles/rubberwhale.png" alt="RubberWhale classic"/> <img src="readmefiles/rubberwhale-convolve.png" alt="RubberWhale convolved"/> 
</p>

#### __Edges detection__

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

##### Histogram Equalization Results 

<p align="center">
	<img src="readmefiles/lena-gray.jpg" alt="Lena Gray"/> <img src="readmefiles/lena-eq.jpg" alt="Equalized Lena"/>
</p>


<p align="center">
	<img src="samples/lena.png" alt="Lena Gray"/> <img src="readmefiles/lenaC-eq.png" alt="Equalized Lena"/>
</p>

### __Fourier transform__

DFT and FFT 2D algorithms provide the ability to work directly 
in the frequency domain.

<p align="center">
	<img src="readmefiles/lena-gray.jpg" alt="Lena Gray"/> <img src="readmefiles/lena-fft.jpg" alt="Lena Gray"/>
</p>

### __Viewer__

The viewer provide an easy and fast way to visualize image processing algorithms.
 
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

### __Image vectorization operation__

#### Threshold example 
```cpp
    mrg::Viewer viewer = mrg::Viewer([](const mrg::Matrix<uint16_t>& img) -> mrg::Matrix<uint16_t>
        {
            auto temp = mrg::Matrix<uint16_t>(img);
            temp[temp < 100] = 0;
            temp[temp >= 100] = 255;
            return temp;
        }
    );
    viewer.show();
```

<p align="center">
	<img src="samples/lena-gray.png" alt="Lena Gray"/> <img src="readmefiles/viewer-threshold.png" alt="Thresholded"/>
</p>
