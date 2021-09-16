#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sfml-system" for configuration "Release"
set_property(TARGET sfml-system APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-system PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./sfml-system.framework/Versions/2.5.1/sfml-system"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-system.framework/Versions/2.5.1/sfml-system"
  )

list(APPEND _IMPORT_CHECK_TARGETS sfml-system )
list(APPEND _IMPORT_CHECK_FILES_FOR_sfml-system "${_IMPORT_PREFIX}/./sfml-system.framework/Versions/2.5.1/sfml-system" )

# Import target "sfml-window" for configuration "Release"
set_property(TARGET sfml-window APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-window PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./sfml-window.framework/Versions/2.5.1/sfml-window"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-window.framework/Versions/2.5.1/sfml-window"
  )

list(APPEND _IMPORT_CHECK_TARGETS sfml-window )
list(APPEND _IMPORT_CHECK_FILES_FOR_sfml-window "${_IMPORT_PREFIX}/./sfml-window.framework/Versions/2.5.1/sfml-window" )

# Import target "sfml-network" for configuration "Release"
set_property(TARGET sfml-network APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-network PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./sfml-network.framework/Versions/2.5.1/sfml-network"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-network.framework/Versions/2.5.1/sfml-network"
  )

list(APPEND _IMPORT_CHECK_TARGETS sfml-network )
list(APPEND _IMPORT_CHECK_FILES_FOR_sfml-network "${_IMPORT_PREFIX}/./sfml-network.framework/Versions/2.5.1/sfml-network" )

# Import target "sfml-graphics" for configuration "Release"
set_property(TARGET sfml-graphics APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-graphics PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-graphics.framework/Versions/2.5.1/sfml-graphics"
  )

list(APPEND _IMPORT_CHECK_TARGETS sfml-graphics )
list(APPEND _IMPORT_CHECK_FILES_FOR_sfml-graphics "${_IMPORT_PREFIX}/./sfml-graphics.framework/Versions/2.5.1/sfml-graphics" )

# Import target "sfml-audio" for configuration "Release"
set_property(TARGET sfml-audio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-audio PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./sfml-audio.framework/Versions/2.5.1/sfml-audio"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-audio.framework/Versions/2.5.1/sfml-audio"
  )

list(APPEND _IMPORT_CHECK_TARGETS sfml-audio )
list(APPEND _IMPORT_CHECK_FILES_FOR_sfml-audio "${_IMPORT_PREFIX}/./sfml-audio.framework/Versions/2.5.1/sfml-audio" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
