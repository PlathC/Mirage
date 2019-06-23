cmake_minimum_required(VERSION 3.14)
project(ImPro)

#include_directories(third/lpng1637)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS " -W")

set(HEADERS
    include/Core/Math.h
    include/Core/Vec.h
    include/Image/Matrix.h
    include/Image/ImageParser.h
    include/Image/Parser/PPMParser.h
    include/Image/Parser/IParser.h
    include/Image/Parser/PngParser.h
    )

set(SOURCES
    main.cpp
    src/Core/Vec.cpp
    src/Image/Matrix.cpp
    src/Image/ImageParser.cpp
    src/Image/Parser/PPMParser.cpp
    src/Image/Parser/IParser.cpp
    src/Image/Parser/PngParser.cpp
    )


add_executable(ImPro ${HEADERS} ${SOURCES})
include_directories(third/lpng1637)

target_link_libraries(ImPro ${CMAKE_CURRENT_SOURCE_DIR}/third/lpng1637/libpng.a -lz)

