#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::WaylandEglCompositorHwIntegrationPrivate" for configuration "RelWithDebInfo"
set_property(TARGET Qt6::WaylandEglCompositorHwIntegrationPrivate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Qt6::WaylandEglCompositorHwIntegrationPrivate PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libQt6WaylandEglCompositorHwIntegration.so.6.2.0"
  IMPORTED_SONAME_RELWITHDEBINFO "libQt6WaylandEglCompositorHwIntegration.so.6"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::WaylandEglCompositorHwIntegrationPrivate )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::WaylandEglCompositorHwIntegrationPrivate "${_IMPORT_PREFIX}/lib/libQt6WaylandEglCompositorHwIntegration.so.6.2.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
