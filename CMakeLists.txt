cmake_minimum_required(VERSION 3.14)
project(Mirage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Weffc++ -Wextra -Wsign-conversion")

set(HEADERS
        include/Mirage/Core/Math.hpp
        include/Mirage/Core/Vec.hpp
        include/Mirage/Image/Matrix.hpp
        include/Mirage/Image/ImageParser.hpp
        include/Mirage/Image/Parser/PPMParser.hpp
        include/Mirage/Image/Parser/IParser.hpp
        include/Mirage/Image/Parser/PngParser.hpp
        include/Mirage/Mirage.hpp)

set(SOURCES
        src/Mirage/Core/Vec.cpp
        src/Mirage/Image/Matrix.cpp
        src/Mirage/Image/ImageParser.cpp
        src/Mirage/Image/Parser/PPMParser.cpp
        src/Mirage/Image/Parser/IParser.cpp
        src/Mirage/Image/Parser/PngParser.cpp
    )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(Mirage ${HEADERS} ${SOURCES})
set_target_properties(Mirage PROPERTIES OUTPUT_NAME "ImPro$<$<CONFIG:Debug>:d>")

include_directories(third/lpng1637)

target_link_libraries(Mirage ${CMAKE_CURRENT_SOURCE_DIR}/third/lpng1637/libpng.a -lz)

