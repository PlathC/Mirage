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
        src/Image/PPMParser.cpp include/Image/PPMParser.h
        src/Image/IParser.cpp include/Image/IParser.h
)

add_executable(ImPro ${SOURCE_FILES})