#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QWebpPlugin" for configuration "RelWithDebInfo"
set_property(TARGET Qt6::QWebpPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Qt6::QWebpPlugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELWITHDEBINFO ""
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/./plugins/imageformats/qwebp.dll"
  )

list(APPEND _cmake_import_check_targets Qt6::QWebpPlugin )
list(APPEND _cmake_import_check_files_for_Qt6::QWebpPlugin "${_IMPORT_PREFIX}/./plugins/imageformats/qwebp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
