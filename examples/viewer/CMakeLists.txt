cmake_minimum_required(VERSION 3.9)
project(MirageViewerExample)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Qt files auto management
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
add_executable(${PROJECT_NAME} main.cpp)
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
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE Mirage)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}$<$<CONFIG:Debug>:d>")

if(MSVC)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    add_custom_target(ViewerDeploy COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE:MirageViewerExample>)
endif()