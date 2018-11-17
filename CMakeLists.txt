cmake_minimum_required(VERSION 3.5)

set(EXTENSION_HOMEPAGE "https://www.nitrc.org/projects/meshmetric3d/")
set(EXTENSION_CATEGORY "Quantification")
set(EXTENSION_CONTRIBUTORS "Francois Budin (UNC), Juliette Pera (UNC), Beatriz Paniagua (UNC)")
set(EXTENSION_DESCRIPTION "This extension computes the distance between two 3D models")
set(EXTENSION_ICONURL "http://slicer.org/slicerWiki/images/4/43/Slicer4ExtensionModelToModelDistance.png")
set(EXTENSION_SCREENSHOTURLS "http://www.slicer.org/slicerWiki/images/thumb/7/7a/Slicer4Extensions-ModelToModelDistanceOriginalShapes.png/800px-Slicer4Extensions-ModelToModelDistanceOriginalShapes.png")
set(EXTENSION_STATUS "")
set(EXTENSION_DEPENDS "NA") # Specified as a space separated list or 'NA' if any
set(EXTENSION_BUILD_SUBDIRECTORY .)

project(3DMetricTools)
set(LOCAL_PROJECT_NAME 3DMetricTools)
set(EXTENSION_NAME ModelToModelDistance)

## This file acts as a simple switch to initiate
## two completely independant CMake build environments.

#-----------------------------------------------------------------------------
# Standalone vs Slicer extension option
#-----------------------------------------------------------------------------

# This option should be named after the project name, it corresponds to the
# option set to ON when the project is build by the Slicer Extension build
# system.

set(_default OFF)
set(_reason "${EXTENSION_NAME}_BUILD_SLICER_EXTENSION is ON")
if(NOT DEFINED ${EXTENSION_NAME}_BUILD_SLICER_EXTENSION AND DEFINED Slicer_DIR)
  set(_default ON)
  set(_reason "Slicer_DIR is SET")
endif()

option(${EXTENSION_NAME}_BUILD_SLICER_EXTENSION "Build as a Slicer Extension" ${_default})

set(_msg "Checking if building as a Slicer extension")
message(STATUS ${_msg})
if(${EXTENSION_NAME}_BUILD_SLICER_EXTENSION)
  message(STATUS "${_msg} - yes (${_reason})")
else()
  message(STATUS "${_msg} - no (${EXTENSION_NAME}_BUILD_SLICER_EXTENSION is OFF)")
endif()

#-----------------------------------------------------------------------------
# Superbuild Option - Enabled by default
#                   Phase I:  ${LOCAL_PROJECT_NAME}_SUPERBUILD is set to ON, and the
#                             supporting packages defined in "SuperBuild.cmake"
#                             are built.  The last package in "SuperBuild.cmake"
#                             to be built is a recursive call to this
#                             file with ${LOCAL_PROJECT_NAME}_SUPERBUILD explicitly
#                             set to "OFF" to initiate Phase II
#
#                   Phase II: Build the ${LOCAL_PROJECT_NAME}, referencing the support
#                             packages built in Phase I.
#-----------------------------------------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/Common.cmake) #<-- All feature options for top superbuild and inner product build

set(_default ON)
if(${EXTENSION_NAME}_BUILD_SLICER_EXTENSION)
  set(_default OFF)
endif()

option(${LOCAL_PROJECT_NAME}_SUPERBUILD "Build ${LOCAL_PROJECT_NAME} and the projects it depends on via SuperBuild.cmake." ${_default})

set(_msg "Checking if enabling Superbuild")
message(STATUS ${_msg})
if(${LOCAL_PROJECT_NAME}_SUPERBUILD)
  message(STATUS "${_msg} - yes")
else()
  message(STATUS "${_msg} - no")
endif()

if(${LOCAL_PROJECT_NAME}_SUPERBUILD)
  include("${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild.cmake") #<-- Harness for managing top superbuild, and finally delegate inner product build
  return()
else()
  include("${CMAKE_CURRENT_SOURCE_DIR}/${LOCAL_PROJECT_NAME}.cmake") #<-- inner product build (a separate build environment from top level build)
  return()
endif()

