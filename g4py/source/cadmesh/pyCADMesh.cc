// ====================================================================
//   pyCADMesh.cc
// ====================================================================
#include <boost/python.hpp>
#include "CADMesh.hh"

using namespace boost::python;

// ====================================================================
// function overloads
// ====================================================================
G4VSolid*	(CADMesh::*TessellatedMesh_int)(int)	= &CADMesh::TessellatedMesh;
G4VSolid*	(CADMesh::*TessellatedMesh_none)()	= &CADMesh::TessellatedMesh;
G4VSolid*	(CADMesh::*TessellatedMesh_g4string)(G4String)	= &CADMesh::TessellatedMesh;

// ====================================================================
// module definition
// ====================================================================
void export_CADMesh() {

  class_<CADMesh, CADMesh*>
    ("CADMesh", "CADMesh importer class", no_init)
    // constructors
    .def(init<char *, double, G4ThreeVector, G4bool>())
    .def(init<char *, char *, double, G4ThreeVector, G4bool>())
    .def(init<char *, char *, G4Material *, double>())
    .def(init<char *, char *, G4Material *, double, G4ThreeVector>())
    .def(init<char *, char*>())
    .def(init<char *, char*, G4Material *>())

    // methods
#ifndef NOTET
    .def("TetrahedralMesh",	&CADMesh::TetrahedralMesh, return_value_policy<manage_new_object>())
    .def("GetAssembly",	&CADMesh::GetAssembly, return_value_policy<reference_existing_object>())
    .def("get_input_point_count",	&CADMesh::get_input_point_count)
    .def("get_output_point_count",	&CADMesh::get_output_point_count)
    .def("get_tetrahedron_count",	&CADMesh::get_tetrahedron_count)
#endif

#ifndef NOVCGLIB
    .def("TessellatedMesh", 	&CADMesh::TessellatedMesh, return_value_policy<manage_new_object>())
    .def("GetSolid",    &CADMesh::GetSolid, return_value_policy<reference_existing_object>())
    .def("MeshName",    &CADMesh::MeshName)
    .def("MeshVertexNumber",    &CADMesh::MeshVertexNumber)
    .def("SetVerbose",  &CADMesh::SetVerbose)
#endif

#ifndef NOASSIMP
    .def("TessellatedMesh", TessellatedMesh_int, return_value_policy<manage_new_object>())
    .def("TessellatedMesh", TessellatedMesh_none, return_value_policy<manage_new_object>())
    .def("TessellatedMesh", TessellatedMesh_g4string, return_value_policy<manage_new_object>())
    .def("GetSolid",	&CADMesh::GetSolid, return_value_policy<reference_existing_object>())
    .def("MeshName",	&CADMesh::MeshName)
    .def("SetVerbose",	&CADMesh::SetVerbose)
#endif
    ;

}

