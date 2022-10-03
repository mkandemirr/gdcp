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

#include "NuSDPmtROUnitBuilder.hh"
#include "NuSDPmtROUnitBuilderMessenger.hh"
#include "VComponentBuilder.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
//#include "G4RotationMatrix.hh"
#include "TrdComponentBuilder.hh"
#include "BoxComponentBuilder.hh"
#include "TubsComponentBuilder.hh"
#include "G4SolidStore.hh"
#include "G4Material.hh"
#include "NuSDDetectorBuilder.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "GeometryManager.hh"
#include "NuSDVDetUnitCompBuilder.hh"
#include "G4LogicalSkinSurface.hh"
#include "MaterialPropertiesHelper.hh"
#include "OpticalSurface.hh"
#include "SmartComponent.hh"
//#include "G4RunManager.hh"
//#include "G4StateManager.hh"

#include "G4UImanager.hh"
#include "NuSDMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDPmtROUnitBuilder::NuSDPmtROUnitBuilder(const G4String& name, const G4String& matName, NuSDAxisType placedAxis) : NuSDVROUnitCompBuilder(name, matName, placedAxis),
fMessenger{nullptr},
fReflectorMatProp{nullptr},
fReflectorSurface{nullptr},
fLgBinderBuilder{nullptr},
fLgBuilder{nullptr},
fPSBinderBuilder{nullptr},
fPSBuilder{nullptr},
bReflector{false},
bLg{false},
bLgBinder{false},
bPSBinder{false}
               
{
  fMessenger = new NuSDPmtROUnitBuilderMessenger(this);
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  uImanager->ApplyCommand("/control/execute macros/readout/"+pName+".mac"); 
  
  pProduct = new SmartComponent(pName);
  CreateSubComponentBuilders();
  
  //---
  fReflectorMatProp = new MaterialPropertiesHelper(pName);
  uImanager->ApplyCommand("/control/execute macros/matPropTable/"+pName+".mac");
  
  fReflectorSurface = new OpticalSurface(pName);  
  uImanager->ApplyCommand("/control/execute macros/opticalSurface/"+pName+".mac");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDPmtROUnitBuilder::~NuSDPmtROUnitBuilder()
{ 
  if(fMessenger) delete fMessenger;
  if(pProduct)   delete pProduct;
  if(fReflectorMatProp) delete fReflectorMatProp;
  if(fReflectorSurface) delete fReflectorSurface;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::CreateSubComponentBuilders()
{
  //Create sub component builders
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
  //Dimensions will be updated later and controlled by user interface commands
  if(bLgBinder)
  {
    fLgBinderBuilder = new BoxComponentBuilder("LightGuideBinder"+axisLtr,"Air", matFactory, 15.*mm, 15.*mm, 15.*mm);
    uImanager->ApplyCommand("/control/execute macros/boxComponent/"+fLgBinderBuilder->GetName()+".mac"); 
  }
         
  if(bLg)
  {
    fLgBuilder = new TrdComponentBuilder("LightGuide"+axisLtr,"Pmma",matFactory,2.*cm, 6.*cm, 2.*cm, 6.*cm, 5.*cm);
    uImanager->ApplyCommand("/control/execute macros/trdComponent/"+fLgBuilder->GetName()+".mac");  
  }
    
  if(bPSBinder)
  {
    fPSBinderBuilder  = new TubsComponentBuilder("PhotoCathodeBinder"+axisLtr, "Air",matFactory, 0., 6*cm, 10*mm, 0*deg, 360*deg);
    uImanager->ApplyCommand("/control/execute macros/tubsComponent/"+fPSBinderBuilder->GetName()+".mac"); 
  }    
  
  fPSBuilder = new TubsComponentBuilder("PhotoCathode"+axisLtr, "G4_Al", matFactory, 0., 5*cm, 5*cm, 0*deg, 360*deg);   
  uImanager->ApplyCommand("/control/execute macros/tubsComponent/"+fPSBuilder->GetName()+".mac");
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::CreateMaterial()
{
  pMaterial = NuSDMaterialFactory::GetInstance()->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::Construct()
{
  CreateMaterial();
  
  if(bLgBinder) 
    fLgBinderBuilder->Construct(); 
    
  if(bLg) 
    fLgBuilder->Construct();
    
  if(bPSBinder) 
    fPSBinderBuilder->Construct();
    
  if(fPSBuilder) 
    fPSBuilder->Construct();
 
  //adjust components dimensions
  G4ThreeVector unitHalfSize; 
  SetComponentsDimensions(unitHalfSize);
      
  G4Box  *unitSolid           = new G4Box (pName+"Solid", unitHalfSize.x(), unitHalfSize.y(), unitHalfSize.z());
  G4LogicalVolume *unitLogic  = new G4LogicalVolume(unitSolid, pMaterial, pName+"Logic");

  pProduct->SetLogicalVolume(unitLogic); 
  //--
  SetPrivateSurfaceAndMaterialProperties(); 
  PlaceSubComponents();
           
}

void NuSDPmtROUnitBuilder::SetPrivateSurfaceAndMaterialProperties()
{
  //Set Reflector
  if(bReflector)
  {
    //fReflectorSurface->SetMaterialPropertiesTable(fReflectorMatProp);
    fReflectorMatProp->AddPropertiesToSurface(fReflectorSurface);
    new G4LogicalSkinSurface("ReflectorSkinSurf", pProduct->GetLogicalVolume(), fReflectorSurface );
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::PlaceSubComponents()
{
  //adjust positions
  G4ThreeVector lgBinderPos;
  G4ThreeVector lgPos;
  G4ThreeVector psBinderPos;
  G4ThreeVector psPos;
  
  SetComponentsPositions(lgBinderPos,lgPos,psBinderPos,psPos);
  
  //adjust rotations
  G4RotationMatrix* lgBinderRot{nullptr};
  G4RotationMatrix* lgRot{nullptr};
  G4RotationMatrix* psBinderRot{nullptr};
  G4RotationMatrix* psRot{new G4RotationMatrix};

  if(bLgBinder)  lgBinderRot = new G4RotationMatrix;
  if(bLg)        lgRot       = new G4RotationMatrix;
  if(bPSBinder) psBinderRot  = new G4RotationMatrix;
  
  SetComponentsRotations(lgBinderRot,lgRot,psBinderRot,psRot);
  
  
  //--------------Placement-------------------------
  G4VPhysicalVolume* physVol{nullptr};
  
  //place lightGuideBinder
  if(bLgBinder)
  {
    physVol = new G4PVPlacement(lgBinderRot,                     //no rotation
                  lgBinderPos,      
                  fLgBinderBuilder->GetProduct()->GetLogicalVolume(),         //its logical volume
                  "LgBinderPV",               //its name
                  pProduct->GetLogicalVolume(),   //its mother  volume
                  false,                 //no boolean operation
                  0,                     //copy number
                  true            //overlaps checking 
                  ); 
    
    fLgBinderBuilder->GetProduct()->SetPhysicalVolume(physVol);                  
                                         
  }  
   
  //place lightGuide 
  if(bLg)
  {

    physVol = new G4PVPlacement(lgRot, 
                  lgPos,      //at (0,0,0)
                  fLgBuilder->GetProduct()->GetLogicalVolume(),         //its logical volume
                  "LightGuidePV",               //its name
                  pProduct->GetLogicalVolume(),   //its mother  volume
                  false,                 //no boolean operation
                  1,                     //copy number
                  true          //overlaps checking 
                  ); 
              
    fLgBuilder->GetProduct()->SetPhysicalVolume(physVol);                     

  }                                                                    
  
  //place photoSensorBinder                 
  if(bPSBinder)
  {

    physVol = new G4PVPlacement(psBinderRot,                     
                  psBinderPos,    
                  fPSBinderBuilder->GetProduct()->GetLogicalVolume(),         //its logical volume
                  "PSBinderPV",               //its name
                  pProduct->GetLogicalVolume(),   //its mother  volume
                  false,                 //no boolean operation
                  2,                     //copy number
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
                  3,                     //copy number
                  true        //overlaps checking
                  );         
    
    fPSBuilder->GetProduct()->SetPhysicalVolume(physVol);    
  
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::SetComponentsDimensions(G4ThreeVector& unitHalfSize)
{ 
  G4double unitHalfLength = fPSBuilder->GetZHalfLength(); //minimum value
                      
  //common for all axis.
  if(bPSBinder)
  {
    fPSBinderBuilder->SetOuterRadius(fPSBuilder->GetOuterRadius());
    unitHalfLength += fPSBinderBuilder->GetZHalfLength();
  }
  
  //common for all axis
  if(bLg)
  {
    unitHalfLength += fLgBuilder->GetZHalfLength();      
  }
     
  //Set the dimensions of LightGuide and LightGuideBinder.
  NuSDDetectorBuilder* detBuilder = static_cast<NuSDDetectorBuilder*>(pGeometryManager->GetDetBuilder());
  
  const VComponentBuilder* attachedComp = detBuilder->GetDetUnitBuilder()->GetSensorAttachedComponent();
  G4Box* attachedBox{nullptr};
  
  if(attachedComp)
    attachedBox = (G4Box*)attachedComp->GetConstProduct()->GetLogicalVolume()->GetSolid();
  
  G4Box* detUnitBox = (G4Box*)detBuilder->GetDetUnitBuilder()->
                      GetProduct()->GetLogicalVolume()->GetSolid();
  
  if(pPlacedAxis == NuSDAxisType::eXAxis)
  {
    if(bLgBinder)
    {
      unitHalfLength += fLgBinderBuilder->GetXHalfLength();
      if(attachedBox)
      {
        fLgBinderBuilder->SetYHalfLength(attachedBox->GetYHalfLength());
        fLgBinderBuilder->SetZHalfLength(attachedBox->GetZHalfLength());  
      }
      
    }
    
    if(bLg && attachedBox)
    {
      fLgBuilder->SetYHalfLength2(attachedBox->GetYHalfLength());
      fLgBuilder->SetXHalfLength2(attachedBox->GetZHalfLength());           
    }
                                                 
    unitHalfSize = G4ThreeVector(unitHalfLength, detUnitBox->GetYHalfLength(), detUnitBox->GetZHalfLength() );
       
  }else if(pPlacedAxis==NuSDAxisType::eYAxis)
  {
    if(bLgBinder)
    {
      unitHalfLength += fLgBinderBuilder->GetYHalfLength();
      if(attachedBox)
      {
        fLgBinderBuilder->SetXHalfLength(attachedBox->GetXHalfLength());
        fLgBinderBuilder->SetZHalfLength(attachedBox->GetZHalfLength());  
      }
      
    }
    
    if(bLg && attachedBox)
    {
      fLgBuilder->SetXHalfLength2(attachedBox->GetXHalfLength());
      fLgBuilder->SetYHalfLength2(attachedBox->GetZHalfLength());            
    }
          
    unitHalfSize = G4ThreeVector(detUnitBox->GetXHalfLength(), unitHalfLength, detUnitBox->GetZHalfLength() );   
        
  }else if(pPlacedAxis==NuSDAxisType::eZAxis)
  {
    if(bLgBinder)
    {
      unitHalfLength += fLgBinderBuilder->GetZHalfLength();
      if(attachedBox)
      {
        fLgBinderBuilder->SetXHalfLength(attachedBox->GetXHalfLength());
        fLgBinderBuilder->SetYHalfLength(attachedBox->GetYHalfLength()); 
      }
      
    }
    
    if(bLg && attachedBox)
    {
      fLgBuilder->SetXHalfLength2(attachedBox->GetXHalfLength());
      fLgBuilder->SetYHalfLength2(attachedBox->GetYHalfLength());             
    }
                     
    unitHalfSize = G4ThreeVector(detUnitBox->GetXHalfLength(), detUnitBox->GetYHalfLength(), unitHalfLength );
          
  }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::SetComponentsPositions(G4ThreeVector& lgBinderPos, 
                                                G4ThreeVector& lgPos, 
                                                G4ThreeVector& psBinderPos, 
                                                G4ThreeVector& psPos
                                                )
{
   
  G4double lgLength{0.};
  G4double lgBinderLength{0.};
  G4double psBinderLength{0.};
  G4double psLength = 2*fPSBuilder->GetZHalfLength();
  
  if(bLg)         lgLength        = 2*fLgBuilder->GetZHalfLength(); 
  if(bPSBinder)  psBinderLength  = 2*fPSBinderBuilder->GetZHalfLength(); 
      
  G4double unitLength{0.};
  
  if(pPlacedAxis==NuSDAxisType::eXAxis)
  {
    if(bLgBinder) lgBinderLength = 2*fLgBinderBuilder->GetXHalfLength();
      
    unitLength = lgBinderLength+lgLength+psBinderLength+psLength;
    
    G4ThreeVector unitStartingPos(unitLength*0.5,0,0); //Wrt unit center!!
    
    lgBinderPos 	 = unitStartingPos - G4ThreeVector(lgBinderLength*0.5,0,0);
    lgPos 				 = unitStartingPos - G4ThreeVector(lgBinderLength+lgLength*0.5,0,0);
    psBinderPos    = unitStartingPos - G4ThreeVector(lgBinderLength+lgLength+psBinderLength*0.5,0,0);
    psPos          = unitStartingPos - G4ThreeVector(lgBinderLength+lgLength+psBinderLength + 
                     psLength*0.5,0,0);

  }else if(pPlacedAxis==NuSDAxisType::eYAxis)
  {
    if(bLgBinder) lgBinderLength = 2*fLgBinderBuilder->GetYHalfLength();
    
    unitLength = lgBinderLength+lgLength+psBinderLength+psLength;
    
   //Binder, Lg, Binder1 and ps position wrt to Pmt PhysicalVolume
    G4ThreeVector unitStartingPos(0,unitLength*0.5,0); //Wrt unit center!!
    
    lgBinderPos    = unitStartingPos - G4ThreeVector(0,lgBinderLength*0.5,0);
    lgPos          = unitStartingPos - G4ThreeVector(0,lgBinderLength+lgLength*0.5,0);
    psBinderPos    = unitStartingPos - G4ThreeVector(0,lgBinderLength+lgLength+psBinderLength*0.5,0);
    psPos          = unitStartingPos - G4ThreeVector(0,lgBinderLength+lgLength+psBinderLength +    
                     psLength*0.5, 0);   

  }else if(pPlacedAxis==NuSDAxisType::eZAxis)
  {
    if(bLgBinder) lgBinderLength = 2*fLgBinderBuilder->GetZHalfLength();
    
    unitLength = lgBinderLength+lgLength+psBinderLength+psLength;

    G4ThreeVector unitStartingPos(0,0,unitLength*0.5); //Wrt pmtunit center
    
    lgBinderPos 		= unitStartingPos - G4ThreeVector(0,0,lgBinderLength*0.5);
    lgPos 					= unitStartingPos - G4ThreeVector(0,0,lgBinderLength+lgLength*0.5);
    psBinderPos 	  = unitStartingPos - G4ThreeVector(0,0,lgBinderLength+lgLength+psBinderLength*0.5);
    psPos           = unitStartingPos - G4ThreeVector(0,0,lgBinderLength+lgLength+psBinderLength+   
                      psLength*0.5);
    
  } 
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::SetComponentsRotations(G4RotationMatrix* lgBinderRot,
                                                G4RotationMatrix* lgRot, 
                                                G4RotationMatrix* psBinderRot, 
                                                G4RotationMatrix* psRot
                                               )
{

  if(pPlacedAxis==NuSDAxisType::eXAxis)
  {
    if(lgBinderRot) lgBinderRot->rotateY(0*deg);
    if(psBinderRot) psBinderRot->rotateY(90*deg);
    if(lgRot) lgRot->rotateY(-90*deg);
    
    psRot->rotateY(90*deg);
    
  }else if(pPlacedAxis==NuSDAxisType::eYAxis)
  {
  
    if(lgBinderRot) lgBinderRot->rotateX(0*deg);
    if(psBinderRot) psBinderRot->rotateX(90*deg);
    if(lgRot) lgRot->rotateX(90*deg);
    
    psRot->rotateX(90*deg);
    
    //lgRot = new G4RotationMatrix();
    //lgBinderRot->rotateX(0*deg);
    //psBinderRot->rotateX(90*deg);
    //lgRot->rotateX(90*deg);
    //psRot->rotateX(90*deg);
    
  }else if(pPlacedAxis==NuSDAxisType::eZAxis)
  {
    if(lgBinderRot) lgBinderRot->rotateX(0*deg);
    if(lgRot)       lgRot->rotateX(0*deg);
    if(psBinderRot) psBinderRot->rotateX(0*deg);
    
    psRot->rotateX(0*deg);
    
  }

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::SetReflectorSurfaceFlag(G4bool bl)
{
  bReflector = bl;
  //if(G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit )
   //G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::SetLightGuideFlag(G4bool bl)
{
  bLg = bl;
  //if(G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit )
   //G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::SetLightGuideBinderFlag(G4bool bl)
{
  bLgBinder = bl;
  //if(G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit )
   //G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDPmtROUnitBuilder::SetPhotoSensorBinderFlag(G4bool bl)
{
  
  bPSBinder = bl;

  //if(G4StateManager::GetStateManager()->GetCurrentState() != G4State_PreInit )
  // G4RunManager::GetRunManager()->ReinitializeGeometry();
}




/*
void NuSDPmtROUnitBuilder::Place(const G4VPhysicalVolume* detectorUnit)
{

}
*/
