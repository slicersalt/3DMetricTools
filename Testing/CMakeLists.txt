cmake_minimum_required(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

if( NOT ${EXTENSION_NAME}_BUILD_SLICER_EXTENSION )
  find_package(ITK REQUIRED )
  include( ${ITK_USE_FILE} )
endif()

# Add standard remote object stores to user's
# configuration.
list(APPEND ExternalData_URL_TEMPLATES
  "http://slicer.kitware.com/midas3/api/rest?method=midas.bitstream.download&checksum=%(hash)"
  )

# Setting

set(TestingBinarydirectory ${CMAKE_CURRENT_BINARY_DIR}/Temporary)
set(TestDataDirectory ${CMAKE_CURRENT_SOURCE_DIR}/Data)

set(Input1VTK DATA{Data/Input/model1.vtk} )

if( Build_3DMeshMetric )
  ## Test 1 : testData
  set( MeshMetric_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3DMeshMetric )
  include_directories( ${MeshMetric_SOURCE_DIR} )
  add_executable( testData ${MeshMetric_SOURCE_DIR}/Testing/testData.cxx ${MeshMetric_SOURCE_DIR}/dataM.cxx )
  target_link_libraries( testData ${VTK_LIBRARIES} )
  ExternalData_Add_Test( ModelToModelDistanceData NAME testData COMMAND $<TARGET_FILE:testData>
  ${Input1VTK}
  )
endif()

if( Build_ModelToModelDistance )
  ## Test 2 : ModelToModelDistance.cxx with no inputs
  add_test(NAME ModelToModelDistanceHelp COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:ModelToModelDistance> --help) # Should just display the Usage:
  if( NOT VTK_DEBUG_LEAKS )
    add_executable(ModelToModelDistanceTest vtkTest.cxx)
    target_link_libraries(ModelToModelDistanceTest ModelToModelDistanceLib ${ITK_LIBRARIES} )
    if( NOT Build_Static )
      set_target_properties(ModelToModelDistanceTest PROPERTIES COMPILE_FLAGS "-DBUILD_SHARED_LIBS") # definition of the variable for c++ preprocessor
    endif()

    ## Test 3 : ModelToModelDistance.cxx with inputs
    set(ReferenceVTK DATA{Data/Baseline/sphere_distance.vtk} )
    set(OutputVTK ${TestingBinarydirectory}/sphere_distance_output.vtk)
    set(InputVTK DATA{Data/Input/sphere.vtk} )

    ExternalData_Add_Test( ModelToModelDistanceData NAME ModelToModelDistanceTest COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:ModelToModelDistanceTest>
      --compare
        ${ReferenceVTK}
        ${OutputVTK}
      ModuleEntryPoint
        -s ${InputVTK}
        -t ${InputVTK}
        -o ${OutputVTK}
     )
    ## Test 4 : ModelToModelDistance.cxx with inputs
    set(ReferenceVTK DATA{Data/Baseline/results.vtk} )
    set(OutputVTK ${TestingBinarydirectory}/distanceModel1Model2.vtk )
    ExternalData_Add_Test( ModelToModelDistanceData NAME ModelToModelDistancePointToPointTest COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:ModelToModelDistanceTest>
      --compare
        ${ReferenceVTK}
        ${OutputVTK}
      ModuleEntryPoint
        -s ${Input1VTK}
        -t ${Input1VTK}
        -o ${OutputVTK}
        --distanceType corresponding_point_to_point
     )
  endif()
endif()

# Add a build target to populate the real data.
ExternalData_Add_Target( ModelToModelDistanceData )

