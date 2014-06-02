# Require at least cmake 2.6.0
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# Name of this project
project(BubbleEx)

# Add the project include directory and put all source files in my_project_sources
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB my_project_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

# Local path for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Load ROOT and setup include directory
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

# Load Geant4 through Find and Use files (the Geant4_DIR directory is where
# the Geant4 cmake Find and Use files can be found)
if(NOT DEFINED Geant4_DIR)
	set(Geant4_DIR $ENV{G4INSTALL}/build)
endif(NOT DEFINED Geant4_DIR)
find_package(Geant4 REQUIRED COMPONENTS gdml qt ui_all vis_all)
include(${Geant4_USE_FILE})

# Link the ROOT and Geant4 libraries
add_library(BubbleEx-lib SHARED ${my_project_sources})
set_target_properties(BubbleEx-lib PROPERTIES OUTPUT_NAME BubbleEx)
target_link_libraries(BubbleEx-lib ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

# Add the target executables:
# - BubbleEx
add_executable(BubbleEx-bin BubbleEx.cc)
set_target_properties(BubbleEx-bin PROPERTIES OUTPUT_NAME BubbleEx)
target_link_libraries(BubbleEx-bin ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} BubbleEx-lib)
