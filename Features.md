# Mirage Features

#### __Filter__ 

##### Classic filters 

The following example show how to apply a Gaussian Blur to an image using 
a kernel provide in the library.

<p align="center">
	<img src="readmefiles/rubberwhale.png" alt="RubberWhale classic"/> <img src="readmefiles/rubberwhale-convolve.png" alt="RubberWhale convolved"/> 
</p>

##### Procedural filters 

Another type of convolution is also implemented to ease the work directly with the kernel 
as it can be needed for dilation or erosion.

The following line of code apply a dilation on the `mat` object.

```cpp
mat = Convolve<uint16_t>(mat, &mrg::KernelMax<uint16_t>, 17);
```

<p align="center">
	<img src="readmefiles/rubberwhale.png" alt="RubberWhale classic"/> <img src="readmefiles/rubberwhale-dilated.jpg" alt="RubberWhale convolved"/> 
</p>

#### __Edges detection__

##### Edges detection Results

Original / Canny / Sobel 

<p align="center">
	<img src="readmefiles/HouseDublin.jpg" alt="Dublin Classic"/> 
	<img src="readmefiles/HouseDublin-Canny.jpg" alt="Dublin Canny"/>
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
int main(int argc, char** argv)
{
    QApplication app{argc, argv};

    mrg::Viewer viewer = mrg::Viewer([](const mrg::Matrix<uint16_t>& img) -> mrg::Matrix<uint16_t>
        {
            auto temp = mrg::Matrix<uint16_t>(img);
            if(temp.Channel() > 1)
                temp = mrg::ToGrayScale<uint16_t, uint16_t>(temp);

            return FloydSteinberg(temp);
        }
    );
    viewer.show();

    return app.exec();
}
```

For more details take a look at `examples/viewer/main.cpp`

### __Image vectorization operation__

#### Sobel threshold example 

```cpp
    mrg::Viewer viewer = mrg::Viewer([](const mrg::Matrix<uint16_t>& img) -> mrg::Matrix<uint16_t>
        {
            mrg::Matrix<double> result = Sobel(img);
            result[result < 128.] = 0;
            return mrg::Transform<double, uint16_t>(result, [](const double p){
                return static_cast<uint16_t>(p);
            });
        }
    );
    viewer.show();
```

<p align="center">
	<img src="readmefiles/HouseDublin.jpg" alt="Lena Gray"/> <img src="readmefiles/viewer-canny.png" alt="Thresholded"/>
</p>
