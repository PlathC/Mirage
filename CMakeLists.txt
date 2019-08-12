cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Mirage)

set(Mirage_VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /W4")
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

option(BUILD_VIEWER "Build Mirage viewer (only for Computer)" OFF)
option(BUILD_EXAMPLES "Build Mirage examples" ON)

find_package(PNG REQUIRED)
message(STATUS "Found LibPNG : " ${PNG_INCLUDE_DIRS})

if(${BUILD_VIEWER})
    find_package(Vulkan REQUIRED)
    message(STATUS "Found Vulkan : " ${Vulkan_INCLUDE_DIRS})
    find_package(glfw3 REQUIRED)
    include_directories(${GLFW3_INCLUDE_DIRS})
    find_package(GLM REQUIRED)
    include_directories(${GLM_INCLUDE_DIRS})

    set(HEADERS
            include/Mirage/Core/Math.hpp
            include/Mirage/Core/Vec.hpp
            include/Mirage/Image/Matrix.hpp
            include/Mirage/Image/ImageParser.hpp
            include/Mirage/Image/Parser/PPMParser.hpp
            include/Mirage/Image/Parser/IParser.hpp
            include/Mirage/Image/Parser/PngParser.hpp
            include/Mirage/Mirage.hpp
            include/Mirage/Viewer/Viewer.hpp
            include/Mirage/Core/Macro.hpp)

    set(SOURCES
            src/Mirage/Core/Vec.cpp
            src/Mirage/Image/Matrix.cpp
            src/Mirage/Image/ImageParser.cpp
            src/Mirage/Image/Parser/PPMParser.cpp
            src/Mirage/Image/Parser/IParser.cpp
            src/Mirage/Image/Parser/PngParser.cpp
            src/Mirage/Viewer/Viewer.cpp )
else()
    set(HEADERS
            include/Mirage/Core/Math.hpp
            include/Mirage/Core/Vec.hpp
            include/Mirage/Image/Matrix.hpp
            include/Mirage/Image/ImageParser.hpp
            include/Mirage/Image/Parser/PPMParser.hpp
            include/Mirage/Image/Parser/IParser.hpp
            include/Mirage/Image/Parser/PngParser.hpp
            include/Mirage/Mirage.hpp
            include/Mirage/Core/Macro.hpp)

    set(SOURCES
            src/Mirage/Core/Vec.cpp
            src/Mirage/Image/Matrix.cpp
            src/Mirage/Image/ImageParser.cpp
            src/Mirage/Image/Parser/PPMParser.cpp
            src/Mirage/Image/Parser/IParser.cpp
            src/Mirage/Image/Parser/PngParser.cpp)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Image/Parser
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Mirage/Viewer)

add_library(Mirage STATIC ${HEADERS} ${SOURCES})
target_compile_options(${PROJECT_NAME} INTERFACE -std=c++17)

target_link_libraries(${PROJECT_NAME}
        PNG::PNG
        ${GLFW_STATIC_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Mirage$<$<CONFIG:Debug>:d>")

if(${BUILD_VIEWER})
    target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
    target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
    target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
    target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY})
endif()

if(${BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()
