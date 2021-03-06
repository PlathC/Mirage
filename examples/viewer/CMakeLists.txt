cmake_minimum_required(VERSION 3.13)
project(MirageViewerExample)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Qt files auto management
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${MIRAGE_COMPILATION_FLAGS})

target_link_options(${PROJECT_NAME} PRIVATE ${MIRAGE_LINKER_FLAGS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE Mirage)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}$<$<CONFIG:Debug>:d>")

if(WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    add_custom_target(ViewerDeploy
            COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE:MirageViewerExample>)
endif()