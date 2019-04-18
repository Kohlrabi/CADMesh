/* ************************************************
 * GEANT4 VCGLIB/CAD INTERFACE - basic example
 *
 * File:      cadmesh_example.cc
 *
 * Author:    Christopher M Poole,
 * Email:     mail@christopherpoole.net
 *
 * Date:      20th March, 2011
 **************************************************/

// USER //
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

// GEANT4 //
#include "G4RunManager.hh"
#include "G4UImanager.hh"
//#include "G4UIterminal.hh"
//#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv)
{
    /* generate temporary data file. G4RunManager will throw an exception if
     * ENSDFSTATE.dat is not found.
     * */
    const char *tempdir = getenv("TMPDIR");
    if(!tempdir)
            tempdir = "/tmp";
    G4String data("G4ENSDFSTATEDATA=");
    data += tempdir;
    putenv(const_cast<char*>(data.c_str()));

    G4String temp = tempdir;
    temp += "/ENSDFSTATE.dat";
    std::ofstream outfile(temp);
    outfile.close();

    //G4cout << "Reading GDML file " << argv[1] << "..." << G4endl;
    //G4RunManager *runManager = new G4RunManager;

    G4RunManager* run_manager = new G4RunManager;
    run_manager->SetVerboseLevel(0);
    
    std::remove(temp);

    DetectorConstruction* detector_construction = new DetectorConstruction;

    if (argc == 1) {
        G4cout << "Usage:" << G4endl;
        G4cout << "    cadmesh_example <cad file name> <gdml name> <material> <cad file type, optional>" << G4endl;
        return 0;
    }

    detector_construction->SetCADFilename(argv[1]);
    detector_construction->SetGDMLName(argv[2]);
    detector_construction->SetCADMaterial(argv[3]);
    if (argc == 5) {
        detector_construction->SetCADFiletype(argv[4]);
    }

    run_manager->SetUserInitialization(detector_construction);

    PhysicsList* physics_list = new PhysicsList;
    run_manager->SetUserInitialization(physics_list);

    PrimaryGeneratorAction* primary_generator = new PrimaryGeneratorAction;
    run_manager->SetUserAction(primary_generator);

    run_manager->Initialize();

    G4VisManager* vis_manager = new G4VisExecutive;
    vis_manager->Initialize();

    G4UImanager * ui_manager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    /* Hard-coded macro */
    ui_manager->ApplyCommand("/run/initialize");
    ui_manager->ApplyCommand("/vis/open OGL");
    ui_manager->ApplyCommand("/vis/drawVolume");
    ui_manager->ApplyCommand("/vis/viewer/set/viewpointVector -1 0 0");
    ui_manager->ApplyCommand("/vis/viewer/set/lightsVector -1 0 0");
    ui_manager->ApplyCommand("/vis/viewer/set/style wireframe");
    ui_manager->ApplyCommand("/vis/viewer/set/auxiliaryEdge true");
    ui_manager->ApplyCommand("/vis/viewer/set/lineSegmentsPerCircle 100");
    ui_manager->ApplyCommand("/vis/viewer/set/autoRefresh true");

    ui->SessionStart();
    delete ui; 
    
    return 0;
}


