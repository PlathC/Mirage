![Logo](readmefiles/banniere.png) 

An image processing library for learning purpose in C++17.

[![Build Status](https://travis-ci.org/PlathC/Mirage.svg?branch=master)](https://travis-ci.org/PlathC/Mirage)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e7674eb14f3a4636b98ded41d9cbb42c)](https://www.codacy.com/manual/PlathC/Mirage?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=PlathC/Mirage&amp;utm_campaign=Badge_Grade) 
[![Coverage Status](https://coveralls.io/repos/github/PlathC/Mirage/badge.svg?branch=master)](https://coveralls.io/github/PlathC/Mirage?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

<h2 align="center">The library</h2>

## __Library features__

| Feature                                                         | Progress                                                     |
|-----------------------------------------------------------------|--------------------------------------------------------------|
| Image structure                                                 | Done                                                         |
| Vector operations (see [__Features description__](Features.md)) | Done                                                         |
| Range indexing for matrix                                       | To do                             |
| Parser                                                          | Done (PNG/JPEG)                                              |
| Mirage Viewer                                                   | Done                                                         |

## Image processing features 

See [__detailed features description__](Features.md)

| Feature                                                         | Progress                          |
|-----------------------------------------------------------------|-----------------------------------|
| Image structure                                                 | Done                              |
| Filter (convolution)                                            | Done                              |
| Sobel / Canny                                                   | Done                              |
| Histogram Equalization                                          | Done                              |
| Threshold (Vectorized and Otsu)                                 | Done                              |
| Crop / Scale                                                    | Done                              |
| Rotation                                                        | Done (Square image)               |
| DFT                                                             | Done                              |
| FFT                                                             | Done                              |
| Mask operations                                                 | Done                              |
| Morphological operations                                        | Done                              |
| Floyd-Steinberg                                                 | Done (`examples/viewer/main.cpp`) |
| Adaptive Histogram Equalization                                 | To do                             |
| Pixel type                                                      | To do                             |
| Video support                                                   | To do                             |
| Optimization (Realtime use, GPU - MT)                           | To do                             |
| Color spaces                                                    | To do                             |

<h2 align="center">Build</h2>

## External dependencies 

This project embed most of its third party to ease the installation. However, Qt5 is needed to build the viewer.

| Feature                          | Dependencies |
|----------------------------------|--------------|
| Mirage + example                 | None         | 
| MIRAGE_BUILD_VIEWER              | QT5          | 
 
## Compiler

It is mainly tested on MSVC (VS2019) and g++-9 (see [![Build Status](https://travis-ci.org/PlathC/Mirage.svg?branch=master)](https://travis-ci.org/PlathC/Mirage))



