#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::EntryPointImplementation" for configuration "Debug"
set_property(TARGET Qt6::EntryPointImplementation APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qt6::EntryPointImplementation PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Qt6EntryPointd.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::EntryPointImplementation )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::EntryPointImplementation "${_IMPORT_PREFIX}/lib/Qt6EntryPointd.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
