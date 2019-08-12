cmake_minimum_required(VERSION 3.12)
project(MirageFilterExample)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Mirage)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}$<$<CONFIG:Debug>:d>")