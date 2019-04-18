/* ************************************************
 * GEANT4 CAD INTERFACE
 *
 * File:      TetrahedralMesh.cc
 *
 * Author:    Christopher M Poole,
 * Email:     mail@christopherpoole.net
 *
 * Date:      7th March, 2011
 **************************************************/

// CADMesh //
#include "TetrahedralMesh.hh"


namespace CADMesh
{

TetrahedralMesh::TetrahedralMesh()
{
}


TetrahedralMesh::~TetrahedralMesh()
{
}


G4VSolid* TetrahedralMesh::GetSolid()
{
    return GetSolid(0);
}


G4VSolid* TetrahedralMesh::GetSolid(G4int /*index*/)
{
    // TODO: Get a solid by index.

    return nullptr;
}


G4VSolid* TetrahedralMesh::GetSolid(G4String /*name*/)
{
    // TODO: Get a solid by name.

    return nullptr;
}


G4AssemblyVolume * TetrahedralMesh::GetAssembly()
{
    if (assembly_)
    {
        return assembly_;
    }
    
    assembly_ = new G4AssemblyVolume();

    in_ = std::make_shared<tetgenio>();
    out_ = std::make_shared<tetgenio>();

    char* fn = (char*) file_name_.c_str();

    G4bool do_tet = true;
   
    if (file_type_ == File::STL)
    {
        in_->load_stl(fn);
    }
    
    else if (file_type_ == File::PLY)
    {
        in_->load_ply(fn);
    }
    
    else if (file_type_ == File::TET)
    {
        out_->load_tetmesh(fn, 0);
        do_tet = false;
    }
    
    else if (file_type_ == File::OFF)
    {
        out_->load_off(fn);
        do_tet = false;
    }

    if (do_tet)
    {
        tetgenbehavior* behavior = new tetgenbehavior();
        behavior->nobisect = 1;
        behavior->plc = 1;
        behavior->quality = quality_;

        tetrahedralize(behavior, in_.get(), out_.get());
    }

    G4RotationMatrix* element_rotation = new G4RotationMatrix();
    G4ThreeVector element_position = G4ThreeVector();
    G4Transform3D assembly_transform = G4Translate3D();

    for (int i=0; i<out_->numberoftetrahedra; i++)
    {
        // For a tetrahedron, out_->numberofcorners == 4 
        int index_offset = i * 4;

        G4ThreeVector p1 = GetTetPoint(index_offset);
        G4ThreeVector p2 = GetTetPoint(index_offset + 1);
        G4ThreeVector p3 = GetTetPoint(index_offset + 2);
        G4ThreeVector p4 = GetTetPoint(index_offset + 3);

        G4String tet_name = file_name_
                          + G4String("_tet_")
                          + G4UIcommand::ConvertToString(i);

        auto tet_solid = new G4Tet( tet_name + G4String("_solid")
                                  , p1, p2, p3, p4, 0);

        auto tet_logical = new G4LogicalVolume( tet_solid
                                              , material_
                                              , tet_name + G4String("_logical")
                                              , 0, 0, 0);

        assembly_->AddPlacedVolume( tet_logical
                                  , element_position
                                  , element_rotation);
    }

    return assembly_;
}

G4ThreeVector TetrahedralMesh::GetTetPoint(G4int index_offset)
{
    return G4ThreeVector(
            out_->pointlist[out_->tetrahedronlist[index_offset]*3] * scale_ - offset_.x(),
            out_->pointlist[out_->tetrahedronlist[index_offset]*3+1] * scale_ - offset_.y(),
            out_->pointlist[out_->tetrahedronlist[index_offset]*3+2] * scale_ - offset_.z());
}

} // CADMesh namespace

