# --- define the libarary ---

# define the source files
file(GLOB colorful_SOURCES *.${colorful_SRCEXT})

# define the library and its alias
add_library(colorful STATIC ${colorful_SOURCES})
add_library(colorful::colorful ALIAS colorful)
target_include_directories(colorful PUBLIC
    $<BUILD_INTERFACE:${colorful_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# --- export the library ---

# specify the library targets
install(TARGETS colorful
        EXPORT colorfulTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/colorful
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install the export details
install(EXPORT colorfulTargets
        FILE colorfulTargets.cmake
        NAMESPACE colorful::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/colorful)
