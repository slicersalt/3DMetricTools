
PROJECT( ModelToModelDistance )

set( EXECUTABLE_ONLY_OPTION )
if( Build_Static )
  set( EXECUTABLE_ONLY_OPTION "EXECUTABLE_ONLY" )
endif()

set(install_destination_args)
if(NOT ${EXTENSION_NAME}_BUILD_SLICER_EXTENSION)
  set(install_destination_args
    INSTALL_RUNTIME_DESTINATION ${INSTALL_RUNTIME_DESTINATION}
    INSTALL_LIBRARY_DESTINATION ${INSTALL_LIBRARY_DESTINATION}
    INSTALL_ARCHIVE_DESTINATION ${INSTALL_ARCHIVE_DESTINATION}
    )
endif()

SEMMacroBuildCLI(
  NAME ModelToModelDistance
  ${EXECUTABLE_ONLY_OPTION}
  ADDITIONAL_SRCS
    vtkImplicitPolyDataDistance_m.cxx
    vtkImplicitPolyDataDistance_m.h
    vtkDistancePolyDataFilter_m.cxx
    vtkDistancePolyDataFilter_m.h
  INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
  TARGET_LIBRARIES ${VTK_LIBRARIES}
  ${install_destination_args}
  )

