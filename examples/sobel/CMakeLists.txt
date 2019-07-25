cmake_minimum_required(VERSION 3.14)
project(MirageSobelExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Weffc++ -Wextra -Wsign-conversion")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../third/lpng1637)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-debug/lib)
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    #link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-build-debug/lib)
    SET(MIRAGE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-build-debug/lib/libImProd.a)
else()
    #link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-build-release/lib)
    SET(MIRAGE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-build-release/lib/libImPro.a)
endif()

add_library(Mirage STATIC ${MIRAGE_LIB})
set_target_properties(Mirage PROPERTIES LINKER_LANGUAGE CXX)

add_executable(MirageSobelExample main.cpp)
target_link_libraries(MirageSobelExample ${CMAKE_CURRENT_SOURCE_DIR}/../../third/lpng1637/libpng.a -lz)
