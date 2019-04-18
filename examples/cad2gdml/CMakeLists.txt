cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(cad2gdml)

# GEANT4 core
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Include CADMesh in your project.
# find_package(cadmesh)
# include_directories(${CADMESH_INCLUDE_DIRS})

# User code
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(cad2gdml cad2gdml.cc ${sources} ${headers})
target_link_libraries(cad2gdml ${Geant4_LIBRARIES})

target_link_libraries(cad2gdml cadmesh)
# OR target_link_libraries(cadmesh_example ${cadmesh_LIBRARIES})

