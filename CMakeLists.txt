cmake_minimum_required(VERSION 3.14)
project(ImPro)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImPro main.cpp include/Core/Math.h src/Core/Vec.cpp include/Core/Vec.h src/Image/Matrix.cpp include/Image/Matrix.h src/Image/ImageParser.cpp include/Image/ImageParser.h)