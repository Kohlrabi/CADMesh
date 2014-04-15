// ====================================================================
//   pyCADMesh.cc
// ====================================================================
#include <boost/python.hpp>
#include "G4AssemblyVolume.hh"
#include "G4LogicalVolume.hh"

using namespace boost::python;

// ====================================================================
// function overloads
// ====================================================================
namespace pyG4AssemblyVolume {
	
	void		(G4AssemblyVolume::*AddPlacedVolume_vec_rot)(G4LogicalVolume *, G4ThreeVector &, G4RotationMatrix *) = &G4AssemblyVolume::AddPlacedVolume;
	void		(G4AssemblyVolume::*AddPlacedVolume_tf)(G4LogicalVolume *, G4Transform3D &) = &G4AssemblyVolume::AddPlacedVolume;
	
	void		(G4AssemblyVolume::*AddPlacedAssembly_vec_rot)(G4AssemblyVolume *, G4ThreeVector &, G4RotationMatrix *) = &G4AssemblyVolume::AddPlacedAssembly;
	void		(G4AssemblyVolume::*AddPlacedAssembly_tf)(G4AssemblyVolume *, G4Transform3D &) = &G4AssemblyVolume::AddPlacedAssembly;
	
	void		(G4AssemblyVolume::*MakeImprint_vec_rot)(G4LogicalVolume *, G4ThreeVector &, G4RotationMatrix *, G4int, G4bool) = &G4AssemblyVolume::MakeImprint;
	void		(G4AssemblyVolume::*MakeImprint_tf)(G4LogicalVolume *, G4Transform3D &, G4int, G4bool) = &G4AssemblyVolume::MakeImprint;

}


using namespace pyG4AssemblyVolume;

// ====================================================================
// module definition
// ====================================================================
void export_G4AssemblyVolume() {

  class_<G4AssemblyVolume, G4AssemblyVolume*>
    ("G4AssemblyVolume", "G4AssemblyVolume importer class", no_init)
    // constructors
    .def(init<>())
    .def(init<G4LogicalVolume *, G4ThreeVector &, G4RotationMatrix *>())

    // methods
    .def("AddPlacedVolume", AddPlacedVolume_vec_rot)
    .def("AddPlacedVolume", AddPlacedVolume_tf)
    .def("AddPlacedAssembly", AddPlacedAssembly_vec_rot)
    .def("AddPlacedAssembly", AddPlacedAssembly_tf)
    .def("MakeImprint", MakeImprint_vec_rot)
    .def("MakeImprint", MakeImprint_tf)
    .def("GetVolumesIterator", &G4AssemblyVolume::GetVolumesIterator)
    .def("TotalImprintedVolumes", &G4AssemblyVolume::TotalImprintedVolumes)
    .def("GetImprintsCount", &G4AssemblyVolume::GetImprintsCount)
    .def("GetInstanceCount", &G4AssemblyVolume::GetInstanceCount)
    .def("GetAssemblyID", &G4AssemblyVolume::GetAssemblyID)
    ;
}

