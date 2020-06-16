cmake_minimum_required(VERSION 3.9)
project(MirageFilterExample)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${MIRAGE_COMPILATION_FLAGS})

if(MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:windows /ENTRY:mainCRTStartup)
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE Mirage)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}$<$<CONFIG:Debug>:d>")