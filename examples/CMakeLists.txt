add_subdirectory(filter)
add_subdirectory(sobel)

if(${BUILD_VIEWER})
    add_subdirectory(viewer)
endif()