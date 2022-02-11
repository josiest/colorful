# --- project setup ---
cmake_minimum_required(VERSION 3.13)
project(colorful)
set(colorful_VERSION 0.1.0)

# make cache variables for install destinations
include(GNUInstallDirs)

# compiler flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify file interface
set(colorful_SRCEXT hpp)
set(colorful_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# --- create library ---

add_library(colorful INTERFACE)
target_include_directories(colorful INTERFACE
    $<BUILD_INTERFACE:${colorful_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# -- export library --

# install the target and create the export set
install(TARGETS colorful
        EXPORT colorfulTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# --- create package for library ---

# include helper functions for creating config files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/colorfulConfigVersion.cmake
    VERSION ${colorful_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# generate the package configuration file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/colorfulConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/colorful)

# allow exporting from build tree
export(EXPORT colorfulTargets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/colorfulTargets.cmake
       NAMESPACE colorful::)

# install the export details
install(EXPORT colorfulTargets
        FILE colorfulTargets.cmake
        NAMESPACE colorful::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/colorful)

# install the generated files
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/colorfulConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/colorfulConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/colorful)

# install the include files
install(DIRECTORY ${colorful_INCLUDE_DIR}/colorful
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.${colorful_SRCEXT}")

export(PACKAGE colorful)

if (UNIX)
    set(CMAKE_INSTALL_PREFIX /usr/local)
elseif(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:\\Program Files\\colorful")
endif()
