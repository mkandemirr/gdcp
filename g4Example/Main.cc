//*******************************************************************************
//* Geant4 Detector Construction Pattern (GDCP) Copyright 2022 Mustafa Kandemir *
//*                                                                             *
//* This file is part of GDCP.                                                  *
//*                                                                             *
//* GDCP is free software: you can redistribute it and/or modify it under the   *
//* terms of the GNU General Public License as published by the Free Software   *
//* Foundation, either version 3 of the License, or any later version.          *                                     
//*                                                                             *
//* GDCP is distributed in the hope that it will be useful, but WITHOUT ANY     *
//* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS   * 
//* FOR A PARTICULAR PURPOSE. See the GNU General Public License for more       * 
//* details.                                                                    *
//*                                                                             *                                         
//* You should have received a copy of the GNU General Public License along     *
//* with GDCP. If not, see <https://www.gnu.org/licenses/>.                     *                                                      
//*******************************************************************************

// --------------------------------------------------------------
//                GDCP (Geant4 Detector Construction Pattern)
// --------------------------------------------------------------
//
// Code developed by Mustafa Kandemir
//
//    *******************************
//    *                             *
//    *         Main.cc             *
//    *                             *
//    *******************************

#include "SegmentedDetConstruction.hh"
#include "SolidDetUnitBuilder.hh"
#include "PandaDetUnitBuilder.hh"
#include "G4OpticalPhysics.hh"
#include "FTFP_BERT.hh"
//#include "QGSP_BERT_HP.hh"
//#include "QGSP_BIC_HP.hh"

#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "G4VisExecutive.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace {
  void PrintUsage() 
  {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " GDCP [-b batch ] [-i interactive] [-t nThreads] [-r seed] "
           << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// argc holds the number of arguments (including the name) on the command line
// -> it is ONE when only the name is  given !!!
// argv[0] is always the name of the program
// argv[1] points to the first argument, and so on

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  // Evaluate arguments
  if ( argc > 9 ) {
    PrintUsage();
    return 1;
  }

  G4String batchMacro;
  G4String interactiveMacro;
#ifdef G4MULTITHREADED
  G4int nThreads = 0;
#endif

  G4long myseed = 345354;
  for ( G4int i=1; i<argc; i=i+2 ) 
  {
    if      ( G4String(argv[i]) == "-b" ) batchMacro       = argv[i+1];
    else if ( G4String(argv[i]) == "-i" ) interactiveMacro = argv[i+1];
    else if ( G4String(argv[i]) == "-r" ) myseed           = atoi(argv[i+1]);
#ifdef G4MULTITHREADED
    else if ( G4String(argv[i]) == "-t" ) 
    {
      nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
      G4cout<<"Number of threads: "<<nThreads<<G4endl;
    }
#endif
    else 
    {
      PrintUsage();
      return 1;
    }
  }

  // Instantiate G4UIExecutive if interactive mode
  G4UIExecutive* ui = nullptr;
  if ( batchMacro.size() == 0 ) 
  {
    ui = new G4UIExecutive(argc, argv);
  }
  
  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
#ifdef G4MULTITHREADED
  G4cout << "Using the MT Run Manager (G4MULTITHREADED=ON)" << G4endl;  
  G4MTRunManager* runManager = new G4MTRunManager();
  if ( nThreads > 0 ) runManager->SetNumberOfThreads(nThreads);      
#else
  G4RunManager * runManager = new G4RunManager;
  G4cout << "Using the sequential Run Manager" << G4endl;
#endif

  // Seed the random number generator manually
  G4Random::setTheSeed(myseed);
  
  //PhysicsList  
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);
  
  //Geometry
  SegmentedDetConstruction* detConstruction{nullptr};
  if(interactiveMacro == "solid" || batchMacro == "solid")
    detConstruction = new SegmentedDetConstruction(new SolidDetUnitBuilder("SolidUnit","Air"));
  else if(interactiveMacro == "panda" || batchMacro == "panda")
    detConstruction = new SegmentedDetConstruction(new PandaDetUnitBuilder("PandaUnit","Air"));
  else if(interactiveMacro == "" && batchMacro == "") 
    detConstruction = new SegmentedDetConstruction(new SolidDetUnitBuilder("SolidUnit","Air"));
    
  runManager->SetUserInitialization(detConstruction);
  
  //ActionInitialization
  runManager->SetUserInitialization(new ActionInitialization());
  
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the UI manager and set verbosities
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  uImanager->ApplyCommand("/control/execute macros/initialize.mac"); 
  
  if ( batchMacro.size() ) // Batch mode
  {   
    uImanager->ApplyCommand("/control/execute macros/run.mac");
  }
  else if ( interactiveMacro.size() )// Define UI session Macro for interactive mode
  {
    uImanager->ApplyCommand("/control/execute macros/vis/vis.mac");
    ui->SessionStart();
    delete ui;
  }else // Define UI session Macro for default interactive mode
  {
    uImanager->ApplyCommand("/control/execute macros/vis/vis.mac");
    
    ui->SessionStart();
    delete ui;   
  }

  delete visManager;
  delete runManager;

  return 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
