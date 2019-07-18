cmake_minimum_required(VERSION 3.14)
project(ImPro)

#include_directories(third/lpng1637)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Weffc++ -Wextra -Wsign-conversion")

set(HEADERS
        include/Core/Math.hpp
        include/Core/Vec.hpp
        include/Image/Matrix.hpp
        include/Image/ImageParser.hpp
        include/Image/Parser/PPMParser.hpp
        include/Image/Parser/IParser.hpp
        include/Image/Parser/PngParser.hpp
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

