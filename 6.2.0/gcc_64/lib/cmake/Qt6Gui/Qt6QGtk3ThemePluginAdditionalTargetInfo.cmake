# Additional target information for Qt6QGtk3ThemePlugin
if(NOT DEFINED QT_DEFAULT_IMPORT_CONFIGURATION)
    set(QT_DEFAULT_IMPORT_CONFIGURATION RELWITHDEBINFO)
endif()
__qt_internal_promote_target_to_global_checked(Qt6::QGtk3ThemePlugin)
get_target_property(_qt_imported_location Qt6::QGtk3ThemePlugin IMPORTED_LOCATION_RELWITHDEBINFO)
get_target_property(_qt_imported_location_default Qt6::QGtk3ThemePlugin IMPORTED_LOCATION_${QT_DEFAULT_IMPORT_CONFIGURATION})

# Import target "Qt6::QGtk3ThemePlugin" for configuration "Release"
set_property(TARGET Qt6::QGtk3ThemePlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)

if(_qt_imported_location)
    set_property(TARGET Qt6::QGtk3ThemePlugin PROPERTY IMPORTED_LOCATION_RELEASE "${_qt_imported_location}")
endif()

# Import target "Qt6::QGtk3ThemePlugin" for configuration "MinSizeRel"
set_property(TARGET Qt6::QGtk3ThemePlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)

if(_qt_imported_location)
    set_property(TARGET Qt6::QGtk3ThemePlugin PROPERTY IMPORTED_LOCATION_MINSIZEREL "${_qt_imported_location}")
endif()

# Default configuration
if(_qt_imported_location_default)
    set_property(TARGET Qt6::QGtk3ThemePlugin PROPERTY IMPORTED_LOCATION "${_qt_imported_location_default}")
endif()

unset(_qt_imported_location)
unset(_qt_imported_location_default)
unset(_qt_imported_soname)
unset(_qt_imported_soname_default)
unset(_qt_imported_configs)
