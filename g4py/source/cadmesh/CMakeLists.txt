# - build library

link_directories (${GEANT4_LIBRARY_DIR})

# library
set(_TARGET pyCADMesh)
add_library (
  ${_TARGET} SHARED
  pyCADMesh.cc
  pyG4AssemblyVolume.cc
  pymodCADMesh.cc
)

# CADMesh
find_package(cadmesh)
SET( cadmesh_INCLUDE_DIR "${cadmesh_DIR}/../../../include")
SET( cadmesh_LIBRARY_DIR "${cadmesh_DIR}/../../../lib")
INCLUDE_DIRECTORIES(${cadmesh_INCLUDE_DIR})
FIND_LIBRARY(cadmesh_LIBRARY cadmesh)
SET( cadmesh_libs ${cadmesh_libs} ${cadmesh_LIBRARY})
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOVCGLIB" )

set_target_properties(${_TARGET} PROPERTIES PREFIX "")
set_target_properties(${_TARGET} PROPERTIES OUTPUT_NAME "CADMesh")
set_target_properties(${_TARGET}
                      PROPERTIES INSTALL_RPATH
                      ${GEANT4_LIBRARY_DIR}
                      BUILD_WITH_INSTALL_RPATH TRUE)

target_link_libraries (${_TARGET}
                      ${GEANT4_LIBRARIES_WITH_VIS} boost_python ${cadmesh_libs})


# install
install(TARGETS ${_TARGET} LIBRARY DESTINATION ${G4MODULES_INSTALL_DIR})
