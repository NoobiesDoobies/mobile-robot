#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "kinematics::kinematics" for configuration ""
set_property(TARGET kinematics::kinematics APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(kinematics::kinematics PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libkinematics.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS kinematics::kinematics )
list(APPEND _IMPORT_CHECK_FILES_FOR_kinematics::kinematics "${_IMPORT_PREFIX}/lib/libkinematics.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
