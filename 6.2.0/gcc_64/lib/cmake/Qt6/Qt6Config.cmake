
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was QtConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

cmake_minimum_required(VERSION 3.16...3.21)

include("${CMAKE_CURRENT_LIST_DIR}/Qt6ConfigExtras.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtPublicCMakeVersionHelpers.cmake")
__qt_internal_require_suitable_cmake_version_for_using_qt()

get_filename_component(_qt_cmake_dir "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(_qt_6_config_cmake_dir "${CMAKE_CURRENT_LIST_DIR}")

if (NOT QT_NO_CREATE_TARGETS)
    include("${CMAKE_CURRENT_LIST_DIR}/Qt6Targets.cmake")
    if(NOT QT_NO_CREATE_VERSIONLESS_TARGETS)
        include("${CMAKE_CURRENT_LIST_DIR}/Qt6VersionlessTargets.cmake")
    endif()
else()
    # For examples using `find_package(...)` inside their CMakeLists.txt files:
    # Make CMake's AUTOGEN detect this Qt version properly
    set_directory_properties(PROPERTIES
                             QT_VERSION_MAJOR 6
                             QT_VERSION_MINOR 2
                             QT_VERSION_PATCH 0)
endif()

if(NOT "${QT_HOST_PATH}" STREQUAL "")
    find_package(Qt6HostInfo
                 CONFIG
                 REQUIRED
                 PATHS "${QT_HOST_PATH}"
                       "${QT_HOST_PATH_CMAKE_DIR}"
                 NO_CMAKE_FIND_ROOT_PATH
                 NO_DEFAULT_PATH)
endif()

get_filename_component(_qt_import_prefix "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_qt_import_prefix "${_qt_import_prefix}" REALPATH)
list(APPEND CMAKE_MODULE_PATH "${_qt_import_prefix}")
list(APPEND CMAKE_MODULE_PATH "${_qt_import_prefix}/3rdparty/extra-cmake-modules/find-modules")
list(APPEND CMAKE_MODULE_PATH "${_qt_import_prefix}/3rdparty/kwin")

if(APPLE AND (NOT CMAKE_SYSTEM_NAME OR CMAKE_SYSTEM_NAME STREQUAL "Darwin"))
    # Add module directory to pick up custom Info.plist template for macOS
    list(APPEND CMAKE_MODULE_PATH "${_qt_import_prefix}/macos")
elseif(APPLE AND CMAKE_SYSTEM_NAME STREQUAL "iOS")
    # Add module directory to pick up custom Info.plist template for iOS
    list(APPEND CMAKE_MODULE_PATH "${_qt_import_prefix}/ios")
endif()

set(QT_ADDITIONAL_PACKAGES_PREFIX_PATH "" CACHE STRING
    "Additional directories where find(Qt6 ...) components are searched")

# Collect additional package prefix paths to look for Qt packages, both from command line and the
# env variable.
if(NOT DEFINED _qt_additional_packages_prefix_paths)
    set(_qt_additional_packages_prefix_paths "")

    set(_qt_additional_packages_prefixes "")
    if(QT_ADDITIONAL_PACKAGES_PREFIX_PATH)
        list(APPEND _qt_additional_packages_prefixes ${QT_ADDITIONAL_PACKAGES_PREFIX_PATH})
    endif()
    if(DEFINED ENV{QT_ADDITIONAL_PACKAGES_PREFIX_PATH}
        AND NOT "$ENV{QT_ADDITIONAL_PACKAGES_PREFIX_PATH}" STREQUAL "")
        list(APPEND _qt_additional_packages_prefixes $ENV{QT_ADDITIONAL_PACKAGES_PREFIX_PATH})
    endif()

    foreach(_qt_additional_path IN LISTS _qt_additional_packages_prefixes)
        file(TO_CMAKE_PATH "${_qt_additional_path}" _qt_additional_path)

        # The prefix paths need to end with lib/cmake to ensure the packages are found when
        # cross compiling. Search for REROOT_PATH_ISSUE_MARKER in the qt.toolchain.cmake file for
        # details.
        # We must pass the values via the PATHS options because the main find_package call uses
        # NO_DEFAULT_PATH, and thus CMAKE_PREFIX_PATH values are discarded.
        # CMAKE_FIND_ROOT_PATH values are not discarded and togegher with the PATHS option, it
        # ensures packages from additional prefixes are found.
        if(NOT _qt_additional_path MATCHES "/lib/cmake$")
            string(APPEND _qt_additional_path "/lib/cmake")
        endif()
        list(APPEND _qt_additional_packages_prefix_paths "${_qt_additional_path}")
    endforeach()
    unset(_qt_additional_path)
    unset(_qt_additional_packages_prefixes)
endif()

# Public helpers available to all Qt packages.
include("${CMAKE_CURRENT_LIST_DIR}/QtFeature.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtPublicFinalizerHelpers.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtPublicPluginHelpers.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtPublicTargetHelpers.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtPublicWalkLibsHelpers.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtPublicFindPackageHelpers.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QtPublicDependencyHelpers.cmake")

if(NOT DEFINED QT_CMAKE_EXPORT_NAMESPACE)
    set(QT_CMAKE_EXPORT_NAMESPACE Qt6)
endif()

# Propagate sanitizer flags to both internal Qt builds and user projects.
# Allow opt-out in case if downstream projects handle it in a different way.
set(QT_CONFIGURED_SANITIZER_OPTIONS "")

if(QT_CONFIGURED_SANITIZER_OPTIONS
   AND NOT __qt_sanitizer_options_set
   AND NOT QT_NO_ADD_SANITIZER_OPTIONS)
    set(ECM_ENABLE_SANITIZERS "${QT_CONFIGURED_SANITIZER_OPTIONS}")
    include(
        "${CMAKE_CURRENT_LIST_DIR}/3rdparty/extra-cmake-modules/modules/ECMEnableSanitizers.cmake")
endif()
# Mark that the current directory scope has its sanitizer flags set.
set(__qt_sanitizer_options_set TRUE)

# Find required dependencies, if any.
include(CMakeFindDependencyMacro)
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/Qt6Dependencies.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/Qt6Dependencies.cmake")
    if(NOT Qt6_DEPENDENCIES_FOUND)
        set(Qt6_FOUND FALSE)
        message(FATAL_ERROR "Failed to find Qt Platform dependency: "
            "${Qt6_DEPENDENCY_NOT_FOUND_MESSAGE}")
    endif()
endif()

set(_Qt6_FIND_PARTS_QUIET)
if(Qt6_FIND_QUIETLY)
     set(_Qt6_FIND_PARTS_QUIET QUIET)
endif()

set(__qt_use_no_default_path_for_qt_packages "NO_DEFAULT_PATH")
if(QT_DISABLE_NO_DEFAULT_PATH_IN_QT_PACKAGES)
    set(__qt_use_no_default_path_for_qt_packages "")
endif()

foreach(module ${Qt6_FIND_COMPONENTS})
    if(NOT "${QT_HOST_PATH}" STREQUAL ""
       AND "${module}" MATCHES "Tools$"
       AND NOT "${module}" MATCHES "ShaderTools$"
       AND NOT "${module}" MATCHES "^Tools$"
       AND NOT QT_NO_FIND_HOST_TOOLS_PATH_MANIPULATION)
        # Make sure that a Qt*Tools package is also looked up in QT_HOST_PATH.
        # But don't match QtShaderTools and QtTools which are cross-compiled target package names.
        # Allow opt out just in case.
        # TODO: Handle a hypothetical QT_ADDITIONAL_HOST_PACKAGES_PREFIX_PATH
        #       See QTBUG-94524
        set(__qt_find_package_host_qt_path "${QT_HOST_PATH}/lib/cmake")
        set(__qt_backup_cmake_prefix_path "${CMAKE_PREFIX_PATH}")
        set(__qt_backup_cmake_find_root_path "${CMAKE_FIND_ROOT_PATH}")
        list(PREPEND CMAKE_PREFIX_PATH "${__qt_find_package_host_qt_path}")
        list(PREPEND CMAKE_FIND_ROOT_PATH "${QT_HOST_PATH}")
    endif()

    find_package(Qt6${module}
        ${Qt6_FIND_VERSION}
        ${_Qt6_FIND_PARTS_QUIET}
        PATHS
            ${_qt_cmake_dir}
            ${_qt_additional_packages_prefix_paths}
            ${QT_EXAMPLES_CMAKE_PREFIX_PATH}
            ${__qt_find_package_host_qt_path}
        ${__qt_use_no_default_path_for_qt_packages}
    )

    if(NOT "${__qt_find_package_host_qt_path}" STREQUAL "")
        set(CMAKE_PREFIX_PATH "${__qt_backup_cmake_prefix_path}")
        set(CMAKE_FIND_ROOT_PATH "${__qt_backup_cmake_find_root_path}")
        unset(__qt_backup_cmake_prefix_path)
        unset(__qt_backup_cmake_find_root_path)
        unset(__qt_find_package_host_qt_path)
    endif()

    if (NOT Qt6${module}_FOUND)
        set(_qt_expected_component_config_path
            "${_qt_cmake_dir}/Qt6${module}/Qt6${module}Config.cmake")
        get_filename_component(
            _qt_expected_component_dir_path "${_qt_expected_component_config_path}" DIRECTORY)

        set(_qt_component_not_found_msg
            "\nExpected Config file at \"${_qt_expected_component_config_path}\"")

        if(EXISTS "${_qt_expected_component_config_path}")
            string(APPEND _qt_component_not_found_msg " exists \n")
        else()
            string(APPEND _qt_component_not_found_msg " does NOT exist\n")
        endif()

        set(_qt_candidate_component_dir_path "${Qt6${module}_DIR}")

        if(_qt_candidate_component_dir_path AND
            NOT _qt_expected_component_dir_path STREQUAL _qt_candidate_component_dir_path)
            string(APPEND _qt_component_not_found_msg
               "\nQt6${module}_DIR was computed by CMake or specified on the "
               "command line by the user: \"${_qt_candidate_component_dir_path}\" "
               "\nThe expected and computed paths are different, which might be the reason for "
               "the package not to be found.")
        endif()

        if(Qt6_FIND_REQUIRED_${module})
            set(_Qt_NOTFOUND_MESSAGE
                "${_Qt_NOTFOUND_MESSAGE}Failed to find Qt component \"${module}\". ${_qt_component_not_found_msg}")
        elseif(NOT Qt6_FIND_QUIETLY)
            message(WARNING
                "Failed to find Qt component \"${module}\". ${_qt_component_not_found_msg}")
        endif()

        unset(_qt_expected_component_config_path)
        unset(_qt_expected_component_dir_path)
        unset(_qt_candidate_component_dir_path)
        unset(_qt_component_not_found_msg)
    endif()
endforeach()

if(Qt6_FIND_COMPONENTS AND _Qt_NOTFOUND_MESSAGE)
    set(Qt6_NOT_FOUND_MESSAGE "${_Qt_NOTFOUND_MESSAGE}")
    set(Qt6_FOUND False)
    unset(_Qt_NOTFOUND_MESSAGE)
endif()

__qt_internal_defer_promote_targets_in_dir_scope_to_global()
if(CMAKE_VERSION VERSION_LESS 3.21)
    __qt_internal_check_link_order_matters()
    __qt_internal_check_cmp0099_available()
endif()
