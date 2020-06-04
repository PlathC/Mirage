project(MIRAGE_TESTS)

set(CMAKE_CXX_STANDARD 17)

set(TESTS_SRC

        Mirage/Core/Math.cpp

    Catch2/Catch.hpp
)

add_executable(${PROJECT_NAME} ${TESTS_SRC})

target_include_directories(
        ${PROJECT_NAME}

        PRIVATE

        "${CMAKE_CURRENT_SOURCE_DIR}/Catch2"
)

target_compile_options(${PROJECT_NAME} PRIVATE ${MIRAGE_COMPILATION_FLAGS})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "../include")
target_link_libraries(${PROJECT_NAME} Mirage)