#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16...3.21)
project(Main)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Locate sources and headers for this project, include them compiler search path

include_directories(${PROJECT_SOURCE_DIR}/NuSD/include 
                    ${PROJECT_SOURCE_DIR}/materials/include
                    ${PROJECT_SOURCE_DIR}/gdcp/include
                    ${PROJECT_SOURCE_DIR}/scntDetector/include    
                    ${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS}
                   )
#message("Geant4_INCLUDE_DIR: ${Geant4_INCLUDE_DIR}")
#message("ROOT_INCLUDE_DIR: ${ROOT_INCLUDE_DIRS}")

file(GLOB sources ${PROJECT_SOURCE_DIR}/NuSD/src/*.cc 
                  ${PROJECT_SOURCE_DIR}/materials/src/*.cc 
                  ${PROJECT_SOURCE_DIR}/gdcp/src/*.cc 
                  ${PROJECT_SOURCE_DIR}/scntDetector/src/*.cc    
                  ${PROJECT_SOURCE_DIR}/src/*.cc
    )

file(GLOB headers ${PROJECT_SOURCE_DIR}/NuSD/include/*.hh
                  ${PROJECT_SOURCE_DIR}/materials/include/*.hh
                  ${PROJECT_SOURCE_DIR}/gdcp/include/*.hh
                  ${PROJECT_SOURCE_DIR}/scntDetector/include/*.hh
                  ${PROJECT_SOURCE_DIR}/include/*.hh
    )

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries

add_executable(Main Main.cc ${sources} ${headers}) 
target_link_libraries(Main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

target_include_directories(Main PUBLIC "${PROJECT_BINARY_DIR}")

#----------------------------------------------------------------------------

file(GLOB macro RELATIVE ${PROJECT_SOURCE_DIR}  macros/*.mac  )
file(GLOB macro0 RELATIVE ${PROJECT_SOURCE_DIR} macros/boxComponent/*.mac  )
file(GLOB macro1 RELATIVE ${PROJECT_SOURCE_DIR} macros/tubsComponent/*.mac  )
file(GLOB macro2 RELATIVE ${PROJECT_SOURCE_DIR} macros/trdComponent/*.mac  )
file(GLOB macro3 RELATIVE ${PROJECT_SOURCE_DIR} macros/matPropTable/*.mac  )
file(GLOB macro4 RELATIVE ${PROJECT_SOURCE_DIR} macros/opticalSurface/*.mac  )
file(GLOB macro5 RELATIVE ${PROJECT_SOURCE_DIR} macros/readout/*.mac  )
file(GLOB macro6 RELATIVE ${PROJECT_SOURCE_DIR} macros/materials/*.mac  )
file(GLOB macro7 RELATIVE ${PROJECT_SOURCE_DIR} macros/vis/*.mac  )

file(GLOB_RECURSE data RELATIVE ${PROJECT_SOURCE_DIR} data/*)

foreach(_file ${macro} ${macro0} ${macro1} ${macro2} ${macro3} ${macro4} ${macro5} ${macro6} ${macro7} ${data} ${other_files} )
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_file}
    ${PROJECT_BINARY_DIR}/${_file}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS Main DESTINATION bin)

