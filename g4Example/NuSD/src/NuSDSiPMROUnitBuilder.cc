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

#include "NuSDSiPMROUnitBuilder.hh"
#include "NuSDSiPMROUnitBuilderMessenger.hh"

#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "BoxComponentBuilder.hh"
#include "NuSDMppcCompBuilder.hh"

#include "G4SolidStore.hh"

#include "G4LogicalSkinSurface.hh"
#include "MaterialPropertiesHelper.hh"
#include "OpticalSurface.hh"
#include "NuSDVGrooveCompBuilder.hh"
#include "NuSDGrooveCompBuilderStore.hh"
//#include "G4RunManager.hh"
//#include "G4StateManager.hh"
#include "G4UImanager.hh"
#include "SmartComponent.hh"
#include "NuSDMaterialFactory.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSiPMROUnitBuilder::NuSDSiPMROUnitBuilder(const G4String& name, const G4String& matName, NuSDAxisType placedAxis) : NuSDVROUnitCompBuilder(name, matName, placedAxis),
fMessenger{nullptr},
fReflectorMatProp{nullptr},
fReflectorSurface{nullptr},
fPSBinderBuilder{nullptr},
fPSBuilder{nullptr},
bReflector{false},
bPSBinder{false}             
{
  fMessenger  = new NuSDSiPMROUnitBuilderMessenger(this);
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  uImanager->ApplyCommand("/control/execute macros/readout/"+pName+".mac"); 
  
  pProduct = new SmartComponent(pName);
  
  CreateSubComponentBuilders();
  
  //----
  fReflectorMatProp = new MaterialPropertiesHelper(pName);
  uImanager->ApplyCommand("/control/execute macros/matPropTable/"+pName+".mac");
  
  fReflectorSurface = new OpticalSurface(pName);  
  uImanager->ApplyCommand("/control/execute macros/opticalSurface/"+pName+".mac");
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSiPMROUnitBuilder::~NuSDSiPMROUnitBuilder()
{ 
  if(fMessenger) delete fMessenger;
  if(pProduct)   delete pProduct;
  if(fReflectorMatProp) delete fReflectorMatProp;
  if(fReflectorSurface) delete fReflectorSurface;  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::CreateSubComponentBuilders()
{ 
  G4String axisLtr="";

  if(pPlacedAxis==NuSDAxisType::eXAxis)
  {
    axisLtr ="X";
  } else if(pPlacedAxis==NuSDAxisType::eYAxis)
  {
    axisLtr = "Y";
  }else
  {
    axisLtr = "Z";   
  } 

  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  NuSDMaterialFactory* matFactory = NuSDMaterialFactory::GetInstance();
  //Dimensions will be updated later.. 
  if(bPSBinder)
  {
    fPSBinderBuilder = new BoxComponentBuilder("MppcBinder"+axisLtr,"Grease",matFactory,1500*mm, 1500*mm, 1500*mm);
    uImanager->ApplyCommand("/control/execute macros/boxComponent/"+fPSBinderBuilder->GetName()+".mac");    
  }
  
  fPSBuilder = new NuSDMppcCompBuilder("Mppc"+axisLtr,"G4_Al",1.5*mm, 1.5*mm, 1.5*mm);
  uImanager->ApplyCommand("/control/execute macros/boxComponent/"+fPSBuilder->GetName()+".mac");
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::CreateMaterial()
{
  pMaterial = NuSDMaterialFactory::GetInstance()->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::Construct()
{
  CreateMaterial();
     
  if(bPSBinder) 
    fPSBinderBuilder->Construct();
    
  if(fPSBuilder) 
    fPSBuilder->Construct();
 
  //adjust all components dimensions inside unit
  G4ThreeVector unitHalfSize; 
  SetComponentsDimensions(unitHalfSize);
      
  G4Box  *unitSolid           = new G4Box(pName+"Solid", unitHalfSize.x(), unitHalfSize.y(), unitHalfSize.z());
  G4LogicalVolume *unitLogic  = new G4LogicalVolume(unitSolid, pMaterial, pName+"Logic");

  pProduct->SetLogicalVolume(unitLogic); 
  //---
  SetPrivateSurfaceAndMaterialProperties();
  PlaceSubComponents();             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::SetPrivateSurfaceAndMaterialProperties()
{
  //Set Reflector
  if(bReflector)
  {
    fReflectorSurface->SetMaterialPropertiesTable(fReflectorMatProp);
    new G4LogicalSkinSurface("reflectorSkinSurf", pProduct->GetLogicalVolume(), fReflectorSurface );
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::PlaceSubComponents()
{
  //adjust positions
  G4ThreeVector psBinderPos;
  G4ThreeVector psPos;
  
  SetComponentsPositions(psBinderPos,psPos);
  
  //adjust rotations. It does anything for SiPM.
  G4RotationMatrix* psBinderRot{nullptr};
  G4RotationMatrix* psRot = new G4RotationMatrix;
  
  if(bPSBinder) psBinderRot = new G4RotationMatrix;
  
  SetComponentsRotations(psBinderRot,psRot);
  
  //--------------Placement-------------------------
  G4VPhysicalVolume* physVol{nullptr};
  
  //place photoSensorBinder                 
  if(bPSBinder)
  {
    physVol = new G4PVPlacement(psBinderRot,                     
                  psBinderPos,    
                  fPSBinderBuilder->GetProduct()->GetLogicalVolume(),         //its logical volume
                  "PSBinderPV",               //its name
                  pProduct->GetLogicalVolume(),   //its mother  volume
                  false,                 //no boolean operation
                  0,                     //copy number
                  true          //overlaps checking
                  ); 
              
    fPSBinderBuilder->GetProduct()->SetPhysicalVolume(physVol);                     

  }                                  
  
  //Place photoSensor                  
  if(fPSBuilder)
  { 
    physVol = new G4PVPlacement(psRot, 
                  psPos,                     //no rotation
                  fPSBuilder->GetProduct()->GetLogicalVolume(),         //its logical volume
                  "PhotonSDPV", // dont change this! checking in stepping action
                  pProduct->GetLogicalVolume(),   //its mother  volume
                  false,                 //no boolean operation
                  1,                     //copy number
                  true        //overlaps checking
                  );         
    
    fPSBuilder->GetProduct()->SetPhysicalVolume(physVol);    
  
  }  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::SetComponentsDimensions(G4ThreeVector& unitHalfSize)
{    
  G4double unitHalfLength{0.};
  G4Box* grooveBox=nullptr;
  
  NuSDGrooveCompBuilderStore* store = NuSDGrooveCompBuilderStore::GetInstance();
 
  if(pPlacedAxis==NuSDAxisType::eXAxis)
  {
    if(bPSBinder)
    {
      fPSBinderBuilder->SetYHalfLength(fPSBuilder->GetYHalfLength());
      fPSBinderBuilder->SetZHalfLength(fPSBuilder->GetZHalfLength());
      
      unitHalfLength += fPSBinderBuilder->GetXHalfLength();
    }  
    
    //Get only one groove in x axis 
    for(std::size_t j=0;j<store->size();++j)
    {
      if(store->at(j)->GetPlacedAxis()==NuSDAxisType::eXAxis)
      {
        grooveBox= (G4Box*)store->at(j)->GetProduct()->GetSolid();
        break;
      } 
    }  
         
    unitHalfLength += fPSBuilder->GetXHalfLength();                       
    unitHalfSize    = G4ThreeVector(unitHalfLength, grooveBox->GetYHalfLength(), grooveBox->GetZHalfLength() );
       
  }else if(pPlacedAxis==NuSDAxisType::eYAxis)
  {
    if(bPSBinder)
    {
      fPSBinderBuilder->SetXHalfLength(fPSBuilder->GetXHalfLength());
      fPSBinderBuilder->SetZHalfLength(fPSBuilder->GetZHalfLength());
      
      unitHalfLength += fPSBinderBuilder->GetYHalfLength();
    }
    
    //Get only one groove in y axis 
    for(std::size_t j=0;j<store->size();++j)
    {
      if(store->at(j)->GetPlacedAxis()==NuSDAxisType::eYAxis)
      {
        grooveBox= (G4Box*)store->at(j)->GetProduct()->GetSolid();
        break;
      } 
    }   
    
    unitHalfLength += fPSBuilder->GetYHalfLength();       
    unitHalfSize    = G4ThreeVector(grooveBox->GetXHalfLength(), unitHalfLength, grooveBox->GetZHalfLength() );   
        
  }else if(pPlacedAxis==NuSDAxisType::eZAxis)
  {
    if(bPSBinder)
    {
      fPSBinderBuilder->SetXHalfLength(fPSBuilder->GetXHalfLength());
      fPSBinderBuilder->SetYHalfLength(fPSBuilder->GetYHalfLength());
      
      unitHalfLength += fPSBinderBuilder->GetZHalfLength();
      
    }
    
    //Get only one groove in z axis  
    for(std::size_t j=0;j<store->size();++j)
    {
      if(store->at(j)->GetPlacedAxis()==NuSDAxisType::eZAxis)
      {
        grooveBox= (G4Box*)store->at(j)->GetProduct()->GetSolid();
        break;
      } 
    }   
     
    unitHalfLength += fPSBuilder->GetZHalfLength();
    unitHalfSize    = G4ThreeVector(grooveBox->GetXHalfLength(), grooveBox->GetYHalfLength(), unitHalfLength );
          
  } 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::SetComponentsPositions(G4ThreeVector& psBinderPos, G4ThreeVector& psPos)
{
  
  G4double psBinderLength = 0.; 
  G4double psLength       = 0.;  
  G4double unitLength     = 0.;
  
  if(pPlacedAxis==NuSDAxisType::eXAxis)
  {
    if(bPSBinder) psBinderLength = 2*fPSBinderBuilder->GetXHalfLength(); 
    
    psLength       = 2*fPSBuilder->GetXHalfLength();
    unitLength     = psBinderLength+psLength;
    
    G4ThreeVector unitStartingPos(unitLength*0.5,0,0); //Wrt pmt center!!
    
    psBinderPos    = unitStartingPos - G4ThreeVector(psBinderLength*0.5,0,0);
    psPos          = unitStartingPos - G4ThreeVector(psBinderLength + psLength*0.5,0,0);

  }else if(pPlacedAxis==NuSDAxisType::eYAxis)
  {
    if(bPSBinder) psBinderLength = 2*fPSBinderBuilder->GetYHalfLength(); 
    
    psLength       = 2*fPSBuilder->GetYHalfLength();
    unitLength     = psBinderLength+psLength;
    
   //Binder, Lg, Binder1 and ps position wrt to Pmt PhysicalVolume
    G4ThreeVector unitStartingPos(0,unitLength*0.5,0); //Wrt pmt center!!
    
    psBinderPos    = unitStartingPos - G4ThreeVector(0, psBinderLength*0.5,0);
    psPos          = unitStartingPos - G4ThreeVector(0, psBinderLength + psLength*0.5, 0);   

  }else if(pPlacedAxis==NuSDAxisType::eZAxis)
  {
    if(bPSBinder) psBinderLength = 2*fPSBinderBuilder->GetZHalfLength(); 
    
    psLength    = 2*fPSBuilder->GetZHalfLength();
    unitLength  = psBinderLength+psLength;

    G4ThreeVector unitStartingPos(0,0,unitLength*0.5); //Wrt pmtunit center
    
    psBinderPos = unitStartingPos - G4ThreeVector(0,0, psBinderLength*0.5);
    psPos       = unitStartingPos - G4ThreeVector(0,0, psBinderLength+psLength*0.5);
    
  } 
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::SetComponentsRotations(G4RotationMatrix* psBinderRot, G4RotationMatrix* psRot)
{

  if(pPlacedAxis==NuSDAxisType::eXAxis)
  {
    if(psBinderRot) 
      psBinderRot->rotateY(0*deg);
    
    psRot->rotateY(0*deg);
    
  }else if(pPlacedAxis==NuSDAxisType::eYAxis)
  {
    if(psBinderRot) 
      psBinderRot->rotateX(0*deg);
    
    psRot->rotateX(0*deg);
     
  }else if(pPlacedAxis==NuSDAxisType::eZAxis)
  { 
    if(psBinderRot) 
      psBinderRot->rotateX(0*deg);
    
    psRot->rotateX(0*deg);
    
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::SetReflectorSurfaceFlag(G4bool bl)
{
  bReflector = bl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilder::SetPhotoSensorBinderFlag(G4bool bl)
{
  bPSBinder = bl;
}









