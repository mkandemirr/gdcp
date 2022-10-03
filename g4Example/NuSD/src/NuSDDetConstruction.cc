//***********************************************************************
//* Neutrino Segmented Detector (NuSD) Copyright 2022 Mustafa Kandemir  *
//*                                                                     *
//* This file is part of NuSD.                                          *
//*                                                                     *
//* NuSD is free software: you can redistribute it and/or modify        * 
//* it under the terms of the GNU General Public License as published   *
//* by the Free Software Foundation, either version 3 of the License,   *
//* or any later version.                                               *
//*                                                                     *
//* NuSD is distributed in the hope that it will be useful, but         *
//* WITHOUT ANY WARRANTY; without even the implied warranty of          *
//* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        * 
//* GNU General Public License for more details.                        *
//*                                                                     *
//* You should have received a copy of the GNU General Public License   *
//* along with NuSD. If not, see <https://www.gnu.org/licenses/>.       *
//*                                                                     *
//***********************************************************************

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "GeometryManager.hh"
#include "NuSDDetConstruction.hh"
#include "NuSDDetectorBuilder.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorDirector.hh"
#include "SmartComponent.hh"
#include "NuSDDetectorBuilder.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDDetConstruction::NuSDDetConstruction(NuSDVDetUnitCompBuilder* detUnitBuilder): 
G4VUserDetectorConstruction(),
pGeometryManager{GeometryManager::GetInstance()}, 
fDetBuilder{nullptr},
fDetDirector{nullptr}
{  
  fDetBuilder  = new NuSDDetectorBuilder("detBuilder","Air", detUnitBuilder);   
  fDetDirector = new DetectorDirector(fDetBuilder); 
   
  pGeometryManager->SetDetBuilder(fDetBuilder);
  fDetDirector->Initialize();          
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDDetConstruction::~NuSDDetConstruction()
{
  //if(fDetBuilder)  delete fDetBuilder; 
  if(fDetDirector) delete fDetDirector; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* NuSDDetConstruction::Construct()
{
  SmartComponent *product = fDetDirector->MakeDetector();
  
  //Place detector in world, before placement set the dimensions
  G4Box* box = (G4Box*)product->GetSolid();
  
  G4double detSizeX = 2*box->GetXHalfLength();
  G4double detSizeY = 2*box->GetYHalfLength();
  G4double detSizeZ = 2*box->GetZHalfLength();
  
  G4double gap{2*cm};
  
  G4double worldSizeX = detSizeX + gap;
  G4double worldSizeY = detSizeY + gap;
  G4double worldSizeZ = detSizeZ + gap;
  
  //World
  G4Box *worldSolid           = new G4Box("WorldSolid", 0.5*worldSizeX, 0.5*worldSizeY, 0.5*worldSizeZ);
  G4LogicalVolume *worldLogic = new G4LogicalVolume(worldSolid, G4Material::GetMaterial("Air"), "WorldLogic");
  
  //Place Detector in World  
  G4VPhysicalVolume* detPV  = new G4PVPlacement(0,  //no rotation
                                  G4ThreeVector(0,0,0),  //at (0,0,0)
                                  product->GetLogicalVolume(),  //its logical volume
                                  "DetectorPV",  //its name
                                  worldLogic,    //its mother volume
                                  false,         //no boolean operation
                                  0,             //copy number
                                  true           //overlaps checking 
                                  );  
  
  product->SetPhysicalVolume(detPV);
   
  G4VPhysicalVolume *worldPV  = new G4PVPlacement(0, 
                                    G4ThreeVector(), 
                                    worldLogic, 
                                    "WorldPV", 
                                    0, 
                                    false, 
                                    0
                                    ); 
                                                                                                            
  return worldPV;
                                                                         
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetConstruction::ConstructSDandField() 
{ 
  fDetDirector->ConstructSD();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

