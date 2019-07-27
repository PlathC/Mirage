cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(Mirage)

set(Mirage_VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Weffc++ -Wextra -Wsign-conversion")


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
find_package(PNG REQUIRED)

set(HEADERS
        include/Mirage/Core/Math.hpp
        include/Mirage/Core/Vec.hpp
        include/Mirage/Image/Matrix.hpp
        include/Mirage/Image/ImageParser.hpp
        include/Mirage/Image/Parser/PPMParser.hpp
        include/Mirage/Image/Parser/IParser.hpp
        include/Mirage/Image/Parser/PngParser.hpp
        include/Mirage/Mirage.hpp
        include/Mirage/Viewer/Viewer.hpp)

set(SOURCES
        src/Mirage/Core/Vec.cpp
        src/Mirage/Image/Matrix.cpp
        src/Mirage/Image/ImageParser.cpp
        src/Mirage/Image/Parser/PPMParser.cpp
        src/Mirage/Image/Parser/IParser.cpp
        src/Mirage/Image/Parser/PngParser.cpp
        src/Mirage/Viewer/Viewer.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image/Parser
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Viewer)

add_library(Mirage STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        PNG::PNG
        ${GLFW_STATIC_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Mirage$<$<CONFIG:Debug>:d>")

target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

add_subdirectory(examples)
