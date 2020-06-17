cmake_minimum_required(VERSION 3.13)
project(MirageFilterExample)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${MIRAGE_COMPILATION_FLAGS})

target_link_options(${PROJECT_NAME} PRIVATE ${MIRAGE_LINKER_FLAGS})

target_link_libraries(${PROJECT_NAME} PRIVATE Mirage)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}$<$<CONFIG:Debug>:d>")