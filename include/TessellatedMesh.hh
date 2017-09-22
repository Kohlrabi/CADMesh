/* ************************************************
 * GEANT4 CAD INTERFACE
 *
 * File:      TessellatedMesh.hh
 *
 * Author:    Christopher M Poole,
 * Email:     mail@christopherpoole.net
 *
 * Original:  7th March, 2011
 **************************************************/

#pragma once

// CADMesh //
#include "CADMeshTemplate.hh"

// Open Asset Importer Library //
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

// GEANT4 //
#include "G4String.hh"
#include "G4ThreeVector.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4Tet.hh"
#include "G4AssemblyVolume.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcommand.hh"


namespace CADMesh
{

class TessellatedMesh : public CADMeshTemplate<TessellatedMesh>
{
  public:
    TessellatedMesh()
        : CADMeshTemplate<TessellatedMesh>()
    {
    };

    TessellatedMesh(G4String file_name)
        : CADMeshTemplate<TessellatedMesh>(file_name)
    {
    };

    TessellatedMesh(G4String file_name, G4String file_type)
        : CADMeshTemplate<TessellatedMesh>(file_name, file_type)
    {
    };

    TessellatedMesh(const aiScene* scene);
    ~TessellatedMesh();

  public:
    G4TessellatedSolid* GetSolid();
    G4TessellatedSolid* GetSolid(G4int index);
    G4TessellatedSolid* GetSolid(G4String name);

  public:
    void SetReverse(G4bool reverse) {
        this->reverse_ = reverse;
    };

    G4bool GetReverse() {
        return this->reverse_;
    };

  private:
    const aiScene* scene_;
    aiMesh* mesh_;

    G4bool reverse_;
};

} // CADMesh namespace

