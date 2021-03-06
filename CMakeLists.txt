cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(Mirage)

set(Mirage_VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(MIRAGE_BUILD_VIEWER "Build Mirage viewer" ON)
option(MIRAGE_BUILD_EXAMPLES "Build Mirage examples" ON)
option(MIRAGE_BUILD_TESTS "Build Mirage tests" ON)
option(MIRAGE_COVERAGE "Enable code coverage" OFF)

add_subdirectory(extern/zlib)
list(APPEND ZLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/zlib/")
list(APPEND ZLIB_INCLUDE_DIR "${CMAKE_BINARY_DIR}/extern/zlib/")

if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
        set(ZLIB_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/zlibd.lib)
    else()
        set(ZLIB_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/zlib.lib)
    endif()
elseif(MINGW)
    set(ZLIB_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libzlib.dll.a)
elseif(UNIX)
    set(ZLIB_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libz.so)
endif()

# Work with png and zlib as embedded library
set(PNG_BUILD_ZLIB ON CACHE BOOL "" FORCE)
add_subdirectory(extern/libpng)
list(APPEND PNG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/libpng/")
list(APPEND PNG_INCLUDE_DIR "${CMAKE_BINARY_DIR}/extern/libpng/")

# Force to compile zlib alongside libpng
add_dependencies(png zlib)

add_subdirectory(extern/libjpeg-turbo)
list(APPEND JPEGTURBO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/libjpeg-turbo/")
list(APPEND JPEGTURBO_INCLUDE_DIR "${CMAKE_BINARY_DIR}/extern/libjpeg-turbo/")

# With OpenMP
OPTION (WITH_OpenMP "Use OpenMP" ON)
IF(WITH_OpenMP)
    message("Build with OpenMP support.")
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()

# Based on https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
if (CMAKE_COMPILER_IS_GNUCC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(MIRAGE_COMPILATION_FLAGS
                -Wall
                -Wextra
                -Wshadow
                -pedantic
                -Wnon-virtual-dtor
                -Wold-style-cast
                -Wcast-align
                -Wunused
                -Woverloaded-virtual
                -Wpedantic
                -Wconversion
                -Wsign-conversion
                -Wmisleading-indentation
                -Wduplicated-cond
                -Wduplicated-branches
                -Wlogical-op
                -Wnull-dereference
                -Wuseless-cast
                -Wdouble-promotion
                -Wformat=2)

        if(MIRAGE_COVERAGE)
            message(STATUS "Add coverage compilation flags")

            set(MIRAGE_COMPILATION_FLAGS
                    ${MIRAGE_COMPILATION_FLAGS}
                    -g
                    -O0
                    -fprofile-arcs
                    -ftest-coverage)
            set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
            set(MIRAGE_LINKER_FLAGS
                    ${MIRAGE_LINKER_FLAGS}
                    -lgcov
                    --coverage)
        endif()
    else()
        set(MIRAGE_COMPILATION_FLAGS
                -DNDEBUG
                -Wall
                -Wextra
                -Wshadow
                -pedantic
                -Wnon-virtual-dtor
                -Wold-style-cast
                -Wcast-align
                -Wunused
                -Woverloaded-virtual
                -Wpedantic
                -Wconversion
                -Wsign-conversion
                -Wmisleading-indentation
                -Wduplicated-cond
                -Wduplicated-branches
                -Wlogical-op
                -Wnull-dereference
                -Wuseless-cast
                -Wdouble-promotion
                -Wformat=2)
    endif()
elseif (MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(MIRAGE_COMPILATION_FLAGS
                /permissive
                /w14242
                /w14254
                /w14263
                /w14265
                /w14287
                /we4289
                /w14296
                /w14311
                /w14545
                /w14546
                /w14547
                /w14549
                /w14555
                /w14619
                /w14640
                /w14826
                /w14928)
    else()
        set(MIRAGE_COMPILATION_FLAGS
                /permissive
                /w14242
                /w14254
                /w14263
                /w14265
                /w14287
                /we4289
                /w14296
                /w14311
                /w14545
                /w14546
                /w14547
                /w14549
                /w14555
                /w14619
                /w14640
                /w14826
                /w14928)
    endif()
endif ()

set(HEADERS
        include/Mirage/Core/Math.hpp
        include/Mirage/Core/Vec.hpp
        include/Mirage/Core/Vec.inl
        include/Mirage/Core/Timer.hpp
        include/Mirage/Core/Macro.hpp
        include/Mirage/Image/Matrix.hpp
        include/Mirage/Image/Matrix.inl
        include/Mirage/Image/Operations.hpp
        include/Mirage/Image/Operations.inl
        include/Mirage/Image/Filtering.hpp
        include/Mirage/Image/Filtering.inl
        include/Mirage/Image/ImageParser.hpp
        include/Mirage/Image/ImageParser.inl
        include/Mirage/Image/Parser/IParser.hpp
        include/Mirage/Image/Parser/PngParser.hpp
        include/Mirage/Image/Parser/PngParser.inl
        include/Mirage/Image/Parser/JpegParser.hpp
        include/Mirage/Image/Parser/JpegParser.inl
        include/Mirage/Mirage.hpp)


set(SOURCES
        src/Mirage/Core/Vec.cpp
        src/Mirage/Core/Timer.cpp
        src/Mirage/Image/Matrix.cpp
        src/Mirage/Image/ImageParser.cpp
        src/Mirage/Image/Operations.cpp
        src/Mirage/Image/Parser/IParser.cpp
        src/Mirage/Image/Parser/PngParser.cpp
        src/Mirage/Image/Parser/JpegParser.cpp)

if(${MIRAGE_BUILD_VIEWER})

    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    # Qt files auto management
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    set(HEADERS
            ${HEADERS}
            include/Mirage/Viewer/Viewer.hpp)

    set(SOURCES
            ${SOURCES}
            src/Mirage/Viewer/Viewer.cpp
            src/Mirage/Viewer/Viewer.ui)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image/Parser
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Viewer)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
target_compile_options(${PROJECT_NAME} INTERFACE)

if (CMAKE_COMPILER_IS_GNUCC)
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
elseif (MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup)
    endif()
endif ()


target_compile_options(${PROJECT_NAME} PUBLIC ${MIRAGE_COMPILATION_FLAGS})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(${PROJECT_NAME} PUBLIC ${JPEGTURBO_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${PNG_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
        zlib
        turbojpeg
        png
        )

if(${MIRAGE_BUILD_VIEWER})
    target_link_libraries(${PROJECT_NAME} PRIVATE
            Qt5::Widgets)
endif()

if(${MIRAGE_BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()

if(${MIRAGE_BUILD_TESTS})
    add_subdirectory(test)
endif()

if(NOT MSVC)
    file(COPY samples DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else()
    file(COPY samples DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
endif()

file(GLOB SAMPLESFILES
        "samples/*"
        )
file(COPY ${SAMPLESFILES} DESTINATION samples)

