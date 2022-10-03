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
//
//
#include "PandaDetUnitBuilder.hh"

#include "globals.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "NuSDGammaScntCompBuilder.hh"
#include "BoxComponentBuilder.hh"
#include "OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "MaterialPropertiesHelper.hh"
#include "SmartComponent.hh"
#include "G4UImanager.hh"
#include "NuSDMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PandaDetUnitBuilder::PandaDetUnitBuilder(const G4String& name, const G4String& matName): 
NuSDVDetUnitCompBuilder(name, matName),
fReflectorMatProp{nullptr},
fReflectorSurface{nullptr},
fGammaScnt{nullptr}, fOptBarrier{nullptr}, fReflector{nullptr}
  
{
  pProduct = new SmartComponent(pName);
  
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  
  fReflectorMatProp = new MaterialPropertiesHelper("AluminizedMylar");
  uImanager->ApplyCommand("/control/execute macros/matPropTable/AluminizedMylar.mac");
   
  fReflectorSurface = new OpticalSurface(fReflectorMatProp->GetName());
  uImanager->ApplyCommand("/control/execute macros/opticalSurface/AluminizedMylar.mac");
   
  CreateSubComponentBuilders();
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PandaDetUnitBuilder::~PandaDetUnitBuilder()
{
  if(pProduct)  delete pProduct;

  if(fReflectorMatProp)  delete fReflectorMatProp;
  if(fReflectorSurface) delete fReflectorSurface; 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PandaDetUnitBuilder::CreateSubComponentBuilders()
{ 
  NuSDMaterialFactory* matFactory = NuSDMaterialFactory::GetInstance();
  
  fGammaScnt    = new NuSDGammaScntCompBuilder("GammaScnt","EJ-200", 10*cm, 10*cm, 100*cm);
  fOptBarrier   = new BoxComponentBuilder("OptBarrier","Air", matFactory);
  fReflector    = new BoxComponentBuilder("Reflector","AluminizedMylar", matFactory);
  fGd           = new BoxComponentBuilder("GdLayer", "GdCoating", matFactory);
  
  fOptBarrierThick  = 0.3*mm; //air 0.3mm  
  fReflectorThick   = 250*um; //0.25mm = 250 um 
  fGdThick          = 50*um; //50um=0.05*mm   
  
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  uImanager->ApplyCommand("/control/execute macros/boxComponent/PandaDetUnitBuilder.mac"); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PandaDetUnitBuilder::CreateMaterial()
{ 
  if(!pMaterial)
    pMaterial = NuSDMaterialFactory::GetInstance()->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PandaDetUnitBuilder::Construct()
{
  CreateMaterial();
  //Construct scintillator
  fGammaScnt->Construct();
  
  //Construct optical barrier.Before construction, set the dimensions of optical barrier.
  G4double optBarrierHalfSizeX = fGammaScnt->GetXHalfLength() + fOptBarrierThick;
  G4double optBarrierHalfSizeY = fGammaScnt->GetYHalfLength() + fOptBarrierThick;
  G4double optBarrierHalfSizeZ = fGammaScnt->GetZHalfLength(); 
  
  fOptBarrier->SetXHalfLength(optBarrierHalfSizeX);
  fOptBarrier->SetYHalfLength(optBarrierHalfSizeY);
  fOptBarrier->SetZHalfLength(optBarrierHalfSizeZ);
  
  fOptBarrier->Construct();
  
  //Construct reflector. Before construction, set the dimensions of the reflector
  G4double reflectorHalfSizeX = optBarrierHalfSizeX + fReflectorThick;
  G4double reflectorHalfSizeY = optBarrierHalfSizeY + fReflectorThick;
  G4double reflectorHalfSizeZ = fGammaScnt->GetZHalfLength();
  
  fReflector->SetXHalfLength(reflectorHalfSizeX);
  fReflector->SetYHalfLength(reflectorHalfSizeY);
  fReflector->SetZHalfLength(reflectorHalfSizeZ);
  
  fReflector->Construct();

  //Set the dimensions of gadolinium.
  G4double gdHalfSizeX  = reflectorHalfSizeX + fGdThick;
  G4double gdHalfSizeY  = reflectorHalfSizeY + fGdThick;
  G4double gdHalfSizeZ  = fGammaScnt->GetZHalfLength();

  fGd->SetXHalfLength(gdHalfSizeX);
  fGd->SetYHalfLength(gdHalfSizeY);
  fGd->SetZHalfLength(gdHalfSizeZ);
  
  fGd->Construct();
  
  //Construct detector unit. Set the dimensions of unit
  G4double distGdToUnit{0*cm};
  
  G4double unitHalfSizeX  = gdHalfSizeX + distGdToUnit;
  G4double unitHalfSizeY  = gdHalfSizeY + distGdToUnit;
  G4double unitHalfSizeZ  = gdHalfSizeZ + distGdToUnit;

 //---------------------
  G4Box* unitSolid            = new G4Box("DetectorUnitSolid", unitHalfSizeX, unitHalfSizeY, unitHalfSizeZ);
  G4LogicalVolume* unitLogic  = new G4LogicalVolume(unitSolid, pMaterial , "DetectorUnitLogic");
  
  pProduct->SetLogicalVolume(unitLogic); 
  
  SetPrivateSurfaceAndMaterialProperties();    
  PlaceSubComponents(); 
} 
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PandaDetUnitBuilder::SetPrivateSurfaceAndMaterialProperties()
{
  //fReflectorSurface->SetMaterialPropertiesTable(fReflectorMatProp);
  
  if(fReflectorMatProp)
    fReflectorMatProp->AddPropertiesToSurface(fReflectorSurface);  
  
  new G4LogicalSkinSurface("reflectorSkinSurf", fReflector->GetProduct()->GetLogicalVolume(), fReflectorSurface );
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......                      
  
   
void PandaDetUnitBuilder::PlaceSubComponents()
{  
  
  G4VPhysicalVolume* physVol{nullptr};
  G4bool checkOverlaps = true;
  
  if(!fGammaScnt->GetProduct()->GetPhysicalVolume())
  {
    //Place NuScnt in OptBarrier
    physVol = new G4PVPlacement(0,            //no rotation
                  G4ThreeVector(0,0,0),       //at (0,0,0)
                  fGammaScnt->GetProduct()->GetLogicalVolume(),               //its logical volume
                  "NuScntPV",               //its name
                  fOptBarrier->GetProduct()->GetLogicalVolume(),          //its mother  volume
                  false,                 //no boolean operation
                  0,                     //copy number
                  checkOverlaps
                  );        //overlaps checking 
                  
    fGammaScnt->GetProduct()->SetPhysicalVolume(physVol);
  }   
     
  if(!fOptBarrier->GetProduct()->GetPhysicalVolume())
  {   
    //Place OptBarrier in Reflector
    physVol = new G4PVPlacement(0,                  //no rotation
                  G4ThreeVector(0,0,0),             //at (0,0,0)
                   fOptBarrier->GetProduct()->GetLogicalVolume(),  //its logical volume
                  "OptBarrierPV",                   //its name
                  fReflector->GetProduct()->GetLogicalVolume(),   //its mother  volume
                  false,                            //no boolean operation
                  1,                                //copy number
                  checkOverlaps                    //overlaps checking 
                  );                                
        
    fOptBarrier->GetProduct()->SetPhysicalVolume(physVol);   
  }

  if(!fReflector->GetProduct()->GetPhysicalVolume())
  {
    //place Reflector in Gd
    physVol = new G4PVPlacement(0,                     //no rotation
                  G4ThreeVector(0,0,0),       //at (0,0,0)
                  fReflector->GetProduct()->GetLogicalVolume(),        //its logical volume
                  "ReflectorPV",               //its name
                  fGd->GetProduct()->GetLogicalVolume(),                     //its mother  volume
                  false,                 //no boolean operation
                  2,                     //copy number
                  checkOverlaps
                  );        //overlaps checking 
       
       
    fReflector->GetProduct()->SetPhysicalVolume(physVol);    
  }
     
  //place Gd in Unit
  physVol = new G4PVPlacement(0,       //no rotation
                G4ThreeVector(0,0,0),  //at (0,0,0)
                fGd->GetProduct()->GetLogicalVolume(),               //its logical volume
                "GdPV",                //dont change it!!look at stepping action
                pProduct->GetLogicalVolume(),           //its mother  volume
                false,                 //no boolean operation
                3,                     //copy number
                checkOverlaps         //overlaps checking
                );        
   
  fGd->GetProduct()->SetPhysicalVolume(physVol);  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const VComponentBuilder* PandaDetUnitBuilder::SetSensorAttachedComponent()
{
  return fGammaScnt;
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


