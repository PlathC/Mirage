add_subdirectory(filter)
add_subdirectory(sobel)
add_subdirectory(histeq)

if(${BUILD_VIEWER})
    add_subdirectory(viewer)
endif()