cmake_minimum_required(VERSION 3.14)
project(ImPro)

set(CMAKE_CXX_STANDARD 14)

set(
        SOURCE_FILES
        main.cpp
        include/Core/Math.h
        include/Core/Vec.h src/Core/Vec.cpp
        include/Image/Matrix.h src/Image/Matrix.cpp
        src/Image/ImageParser.cpp include/Image/ImageParser.h
        src/Image/Parser/PPMParser.cpp include/Image/Parser/PPMParser.h
        src/Image/Parser/IParser.cpp include/Image/Parser/IParser.h
        src/Image/Parser/PngParser.cpp include/Image/Parser/PngParser.h)

add_executable(ImPro ${SOURCE_FILES})