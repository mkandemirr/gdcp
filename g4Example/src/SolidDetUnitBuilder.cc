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
#include "SolidDetUnitBuilder.hh"
#include "SolidGrooveCompBuilder.hh"
#include "globals.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "NuSDGammaScntCompBuilder.hh"
#include "NuSDNeutronScntCompBuilder.hh"
#include "BoxComponentBuilder.hh"
#include "OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "MaterialPropertiesHelper.hh"
#include "SolidGrooveCompBuilder.hh"
#include "SmartComponent.hh"
#include "G4UImanager.hh"
#include "NuSDMaterialFactory.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SolidDetUnitBuilder::SolidDetUnitBuilder(const G4String& name, const G4String& matName): 
NuSDVDetUnitCompBuilder(name, matName),
fReflectorMatProp{nullptr},
fReflectorSurface{nullptr},
fGrooveX{nullptr},
fGrooveY{nullptr},
fGrooveZ{nullptr},
fGammaScnt{nullptr}, fOptBarrier{nullptr}, fNeutronScnt{nullptr}, fReflector{nullptr}

{
  pProduct = new SmartComponent(pName);
  
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  
  fReflectorMatProp = new MaterialPropertiesHelper("AluminizedMylar");
  uImanager->ApplyCommand("/control/execute macros/matPropTable/AluminizedMylar.mac");
   
  fReflectorSurface = new OpticalSurface(fReflectorMatProp->GetName());
  uImanager->ApplyCommand("/control/execute macros/opticalSurface/AluminizedMylar.mac");
  
  CreateSubComponentBuilders();
  CreateMaterial();
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SolidDetUnitBuilder::~SolidDetUnitBuilder()
{
  if(pProduct)  delete pProduct;

  if(fReflectorMatProp)  delete fReflectorMatProp;
  if(fReflectorSurface) delete fReflectorSurface;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidDetUnitBuilder::CreateSubComponentBuilders()
{ 
  NuSDMaterialFactory* matFactory= NuSDMaterialFactory::GetInstance();
  
  fGammaScnt    = new NuSDGammaScntCompBuilder("GammaScnt","EJ-200", 10*cm, 10*cm, 10*cm);
  fOptBarrier   = new BoxComponentBuilder("OptBarrier","Air",matFactory);
  fNeutronScnt  = new NuSDNeutronScntCompBuilder("NeutronScnt","EJ-426", 10*cm, 10*cm, 10*cm);
  fReflector    = new BoxComponentBuilder("Reflector","AluminizedMylar",matFactory);
   
  fOptBarrierThick  = 0.3*mm; //air 0.3mm  
  fReflectorThick   = 250*um; //0.25mm = 250 um 
  fNeutronScntThick = 50*um; //50um=0.05*mm   
  
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  uImanager->ApplyCommand("/control/execute macros/boxComponent/SolidDetUnitBuilder.mac"); 
  
  fGrooveX  = new SolidGrooveCompBuilder("GrooveX","Air",NuSDAxisType::eXAxis);
  //fGrooveY  = new SolidGrooveCompBuilder("GrooveY","Air",NuSDAxisType::eYAxis);
  fGrooveZ  = new SolidGrooveCompBuilder("GrooveZ","Air",NuSDAxisType::eZAxis);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidDetUnitBuilder::CreateMaterial()
{
  pMaterial = NuSDMaterialFactory::GetInstance()->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidDetUnitBuilder::Construct()
{
  //Construct scintillator
  fGammaScnt->Construct();
  
  //Construct optical barrier. Before construction, 
  //set the dimensions of the optical barrier.
  G4double optBarrierHalfSizeX  = fGammaScnt->GetXHalfLength();
  G4double optBarrierHalfSizeY  = 0.5*fOptBarrierThick;
  G4double optBarrierHalfSizeZ  = fGammaScnt->GetZHalfLength(); 
  
  fOptBarrier->SetXHalfLength(optBarrierHalfSizeX);
  fOptBarrier->SetYHalfLength(optBarrierHalfSizeY);
  fOptBarrier->SetZHalfLength(optBarrierHalfSizeZ);
  
  fOptBarrier->Construct();
  
  //Construct neutron scnt. Before construction, 
  //set the dimensions of the neutrino scintillator
  G4double neutronScntHalfSizeX = fGammaScnt->GetXHalfLength();
  G4double neutronScntHalfSizeY = 0.5*fNeutronScntThick;
  G4double neutronScntHalfSizeZ = fGammaScnt->GetZHalfLength(); 
  
  fNeutronScnt->SetXHalfLength(neutronScntHalfSizeX);
  fNeutronScnt->SetYHalfLength(neutronScntHalfSizeY);
  fNeutronScnt->SetZHalfLength(neutronScntHalfSizeZ);
  
  fNeutronScnt->Construct();
  
  //Construct reflector. Before construction, 
  //set the dimensions of the reflector
  G4double reflectorHalfSizeX = fGammaScnt->GetXHalfLength() + fReflectorThick;
  G4double reflectorHalfSizeY = fGammaScnt->GetYHalfLength() + optBarrierHalfSizeY + neutronScntHalfSizeY + fReflectorThick;
  G4double reflectorHalfSizeZ = fGammaScnt->GetZHalfLength() + fReflectorThick;
  
  fReflector->SetXHalfLength(reflectorHalfSizeX);
  fReflector->SetYHalfLength(reflectorHalfSizeY);
  fReflector->SetZHalfLength(reflectorHalfSizeZ);
  
  fReflector->Construct();
    
  //Construct detector unit. Set the dimensions of the unit
  G4double distReflectorToUnit{0.*cm};
  
  G4double unitHalfSizeX  = reflectorHalfSizeX + distReflectorToUnit;
  G4double unitHalfSizeY  = reflectorHalfSizeY + distReflectorToUnit;
  G4double unitHalfSizeZ  = reflectorHalfSizeZ + distReflectorToUnit;

 //---------------------
         
  G4Box* unitSolid            = new G4Box("DetectorUnitSolid", unitHalfSizeX, unitHalfSizeY, unitHalfSizeZ);
  G4LogicalVolume* unitLogic  = new G4LogicalVolume(unitSolid, pMaterial, "DetectorUnitLogic");
  
  pProduct->SetLogicalVolume(unitLogic);
  
  //call after solidunit construction,
  //open grooved for fibers inside unit   
  fGrooveX->Construct();
 // fGrooveY->Construct();
  fGrooveZ->Construct();
  
  SetPrivateSurfaceAndMaterialProperties();    
  PlaceSubComponents();                  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidDetUnitBuilder::SetPrivateSurfaceAndMaterialProperties()
{
  //fReflectorSurface->SetMaterialPropertiesTable(fReflectorMatProp);
  
  if(fReflectorMatProp)
    fReflectorMatProp->AddPropertiesToSurface(fReflectorSurface);  
  
  new G4LogicalSkinSurface("ReflectorSkinSurf", fReflector->GetProduct()->GetLogicalVolume(), fReflectorSurface );
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidDetUnitBuilder::PlaceSubComponents()
{
 
  //Place all components(except grooves) in Reflector(Ref).
  //reference point is Ref center. RefCenterVec(0,0,0)
  
  G4double distNuScntCenterToRefCenterAlongY     = fNeutronScnt->GetYHalfLength() + fOptBarrier->GetYHalfLength();
  G4double distOptBarrierCenterToRefCenterAlongY = fGammaScnt->GetYHalfLength()-distNuScntCenterToRefCenterAlongY
                                                   +fOptBarrier->GetYHalfLength();

  G4double distNdCenterToRefCenterAlongY         = distOptBarrierCenterToRefCenterAlongY+fOptBarrier->GetYHalfLength()
                                                   +fNeutronScnt->GetYHalfLength();

  //x and z axis center coincide
  G4ThreeVector nuScntPosVec(0, -distNuScntCenterToRefCenterAlongY, 0);
  G4ThreeVector optBarrierPosVec(0, distOptBarrierCenterToRefCenterAlongY , 0);
  G4ThreeVector ndPosVec(0, distNdCenterToRefCenterAlongY , 0);
  
  G4VPhysicalVolume* physVol{nullptr};
  G4bool checkOverlaps = true;
  
  if(!fGammaScnt->GetProduct()->GetPhysicalVolume())
  {
    //Place NuScnt in Reflector
    physVol = new G4PVPlacement(0,            //no rotation
                  nuScntPosVec,       //at (0,0,0)
                  fGammaScnt->GetProduct()->GetLogicalVolume(),               //its logical volume
                  "NuScntPV",               //its name
                  fReflector->GetProduct()->GetLogicalVolume(),          //its mother  volume
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
                  optBarrierPosVec,             //at (0,0,0)
                  fOptBarrier->GetProduct()->GetLogicalVolume(),  //its logical volume
                  "OptBarrierPV",                   //its name
                  fReflector->GetProduct()->GetLogicalVolume(),   //its mother  volume
                  false,                            //no boolean operation
                  1,                                //copy number
                  checkOverlaps                    //overlaps checking 
                  );                                
        
    fOptBarrier->GetProduct()->SetPhysicalVolume(physVol);   
  }
  
  if(!fNeutronScnt->GetProduct()->GetPhysicalVolume())
  {   
    //Place neutronScnt in Reflector
    physVol = new G4PVPlacement(0,                  //no rotation
                  ndPosVec,             //at (0,0,0)
                  fNeutronScnt->GetProduct()->GetLogicalVolume(),  //its logical volume
                  "NeutronScntPV",                   //its name
                  fReflector->GetProduct()->GetLogicalVolume(),   //its mother  volume
                  false,                            //no boolean operation
                  2,                                //copy number
                  checkOverlaps                    //overlaps checking 
                  );                                
        
    fNeutronScnt->GetProduct()->SetPhysicalVolume(physVol);   
  }
  
  //Place grooveX in NuScnt
  G4ThreeVector groovePosVec(0,0,0);
  
  groovePosVec = G4ThreeVector(0*cm, 3*cm, 3*cm );
		
  //Open a groove in Reflector. fourth and fifth daughter of Ref.
  G4VPhysicalVolume* grooveXPV = new  G4PVPlacement(0,              //no rotation
                                      groovePosVec,                 //at (0,0,0)
                                      fGrooveX->GetProduct()->GetLogicalVolume(), //its logical volume
                                      "GrooveXPV",                  //its name
                                      fReflector->GetProduct()->GetLogicalVolume(),  //its mother  volume
                                      false,                        //no boolean operation
                                      0,                            //copy number
                                      false      //uyarı verecek!!çünkü groove sintilatörü kesiyor 
                                      ); 
      
  fGrooveX->GetProduct()->SetPhysicalVolume(grooveXPV);
  
  /* 
 //Place grooveY in NuScnt  
  groovePosVec = G4ThreeVector(-2*cm, 0*cm, 0*cm );
      
  G4VPhysicalVolume* grooveYPV = new G4PVPlacement(0,     //no rotation
                                     groovePosVec,               
                                     fGrooveY->GetProduct()->GetLogicalVolume(), //its logical volume
                                     "GrooveYPV",                 //its name
                                     fReflector->GetProduct()->GetLogicalVolume(), //its mother  volume
                                     false,       //no boolean operation
                                     1,           //copy number
                                     false         //uyarı verecek!!çünkü groove sintilatörü kesiyor 
                                     );                
  
  fGrooveY->GetProduct()->SetPhysicalVolume(grooveYPV);  
  */
   
  //Place grooveZ in NuScnt 
  groovePosVec = G4ThreeVector(2*cm, 0*cm, 0*cm );
      
  G4VPhysicalVolume* grooveZPV = new  G4PVPlacement(0,    //no rotation
                                      groovePosVec,     
                                      fGrooveZ->GetProduct()->GetLogicalVolume(),  //its logical volume
                                      "GrooveZPV",                   //its name
                                      fReflector->GetProduct()->GetLogicalVolume(),   //its mother  volume
                                      false,        //no boolean operation
                                      2,            //copy number
                                      false          //uyarı verecek!!çünkü groove sintilatörü kesiyor 
                                      );                
  
  fGrooveZ->GetProduct()->SetPhysicalVolume(grooveZPV);
 
  //place Reflector in Unit
  if(!fReflector->GetProduct()->GetPhysicalVolume())
  {
    
    physVol = new G4PVPlacement(0,                     //no rotation
                  G4ThreeVector(0,0,0),       //at (0,0,0)
                  fReflector->GetProduct()->GetLogicalVolume(),         //its logical volume
                  "ReflectorPV",               //its name
                  pProduct->GetLogicalVolume(),   //its mother  volume
                  false,                 //no boolean operation
                  0,                     //copy number
                  checkOverlaps
                  );        //overlaps checking 
       
       
    fReflector->GetProduct()->SetPhysicalVolume(physVol);    
  }
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


