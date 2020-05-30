cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Mirage)

set(Mirage_VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /W4")
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

option(BUILD_VIEWER "Build Mirage viewer" ON)
option(BUILD_EXAMPLES "Build Mirage examples" ON)

find_package(PNG REQUIRED)
message(STATUS "Found LibPNG : " ${PNG_INCLUDE_DIRS})

find_package(JPEGTURBO REQUIRED)
message(STATUS "Found JpegTurbo : " ${JPEGTURBO_INCLUDE_DIR})

set(HEADERS
        include/Mirage/Core/Math.hpp
        include/Mirage/Core/Vec.hpp
        include/Mirage/Core/Timer.hpp
        include/Mirage/Core/Macro.hpp
        include/Mirage/Image/Matrix.hpp
        include/Mirage/Image/ImageParser.hpp
        include/Mirage/Image/Parser/PPMParser.hpp
        include/Mirage/Image/Parser/IParser.hpp
        include/Mirage/Image/Parser/PngParser.hpp
        include/Mirage/Image/Parser/JpegParser.hpp
        include/Mirage/Mirage.hpp)


set(SOURCES
        src/Mirage/Core/Vec.cpp
        src/Mirage/Core/Timer.cpp
        src/Mirage/Image/Matrix.cpp
        src/Mirage/Image/ImageParser.cpp
        src/Mirage/Image/Parser/PPMParser.cpp
        src/Mirage/Image/Parser/IParser.cpp
        src/Mirage/Image/Parser/PngParser.cpp
        src/Mirage/Image/Parser/JpegParser.cpp)

if(${BUILD_VIEWER})

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
            src/MiragE/Viewer/Viewer.ui)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image/Parser
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Viewer)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
target_compile_options(${PROJECT_NAME} INTERFACE)
if (CMAKE_COMPILER_IS_GNUCC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE
                -Wall
                -Wextra
                -pedantic
                -Wwrite-strings
                -std=c++17
                -Wno-psabi
                -Wno-unused-parameter
                -Wno-ignored-qualifiers
                -Wno-deprecated -lstdc++fs)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE
                -DNDEBUG
                -Wall
                -Wextra
                -pedantic
                -Wwrite-strings
                -std=c++17
                -Wno-psabi
                -Wno-unused-parameter
                -Wno-ignored-qualifiers
                -Wno-deprecated -lstdc++fs)
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
elseif (MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE
                /std:c++17
                /Zc:__cplusplus
                /MDd
                /Od
                /EHsc
                /wd4996
                /Zi
                /wd4634
                /wd4635)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE
                /std:c++17
                /Zc:__cplusplus
                /DNDEBUG
                /O2
                /Ob2
                /EHsc
                /Zi
                /wd4996
                /wd4634
                /wd4635)
        target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:windows /ENTRY:mainCRTStartup)
    endif()
endif ()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JPEGTURBO_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
        PNG::PNG
        ${TURBOJPEG_LIBRARIES}
        ${GLFW_STATIC_LIBRARIES})

if(${BUILD_VIEWER})
    target_link_libraries(${PROJECT_NAME} PRIVATE
            Qt5::Widgets)
endif()

if(${BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()
