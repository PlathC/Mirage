add_subdirectory(filter)
add_subdirectory(edgedetection)
add_subdirectory(histeq)

if(${MIRAGE_BUILD_VIEWER})
    add_subdirectory(viewer)
endif()