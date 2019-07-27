include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/MirageConfigVersion.cmake
        VERSION 0.1
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/CMake/MirageConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/MirageConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

## Install all the helper files
install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MirageConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MirageConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
)