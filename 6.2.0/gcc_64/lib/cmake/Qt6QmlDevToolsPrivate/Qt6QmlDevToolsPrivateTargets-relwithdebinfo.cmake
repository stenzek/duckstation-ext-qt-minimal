#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QmlDevToolsPrivate" for configuration "RelWithDebInfo"
set_property(TARGET Qt6::QmlDevToolsPrivate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Qt6::QmlDevToolsPrivate PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libQt6QmlDevTools.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QmlDevToolsPrivate )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QmlDevToolsPrivate "${_IMPORT_PREFIX}/lib/libQt6QmlDevTools.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
