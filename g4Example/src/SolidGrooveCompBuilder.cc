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

#include "SolidGrooveCompBuilder.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "BoxComponentBuilder.hh"
#include "G4LogicalVolume.hh"

#include "G4SolidStore.hh"
#include "SmartComponent.hh"
#include "ComponentBuilderStore.hh"
#include "NuSDMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SolidGrooveCompBuilder::SolidGrooveCompBuilder(const G4String &name, const G4String& matName, NuSDAxisType placedAxis):
NuSDVGrooveCompBuilder(name, matName, placedAxis),
fCore{nullptr},
fInnerClad{nullptr},
fOuterClad{nullptr}
{
  pProduct = new SmartComponent(pName);
  CreateSubComponentBuilders();
  CreateMaterial();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SolidGrooveCompBuilder::~SolidGrooveCompBuilder()
{
}                      

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidGrooveCompBuilder::CreateSubComponentBuilders()
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

  NuSDMaterialFactory* matFactory = NuSDMaterialFactory::GetInstance();
  
  fCore         = new BoxComponentBuilder("Core"+axisLtr,"Polystyrene",matFactory, 1.5*mm,1.5*mm,1.5*mm);
  fInnerClad    = new BoxComponentBuilder("InnerClad"+axisLtr,"Pmma",matFactory, 2.5*mm,2.5*mm,2.5*mm);
  fOuterClad    = new BoxComponentBuilder("OuterClad"+axisLtr,"FluorinatedAcrylic",matFactory, 3.5*mm,3.5*mm,3.5*mm);
  
  fInnerCladThickness  = 0.5*mm;
  fOutherCladThickness = 0.5*mm;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidGrooveCompBuilder::CreateMaterial()
{
  pMaterial = NuSDMaterialFactory::GetInstance()->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidGrooveCompBuilder::Construct()
{
  fCore->Construct();
  fInnerClad->Construct();
  fOuterClad->Construct();
  
  //adjust component dimension
  G4ThreeVector grooveHalfSize; 
  SetComponentsDimensions(grooveHalfSize);
      
  G4Box  *grooveSolid           = new G4Box (pName+"Solid", grooveHalfSize.x(), grooveHalfSize.y(), grooveHalfSize.z());
  G4LogicalVolume *grooveLogic  = new G4LogicalVolume(grooveSolid, pMaterial, pName+"Logic");

  pProduct->SetLogicalVolume(grooveLogic);
  
  PlaceSubComponents(); 
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidGrooveCompBuilder::PlaceSubComponents()
{
  //PLACEMENT
  
  //-------------------PLACEMENT---------------------------
   new G4PVPlacement(0,
       G4ThreeVector(0.,0.,0.),
       fCore->GetProduct()->GetLogicalVolume(),
       "CorePV", 
       fInnerClad->GetProduct()->GetLogicalVolume(),
       false,
       0,
       true);
  
   new G4PVPlacement(0,
       G4ThreeVector(0.,0.,0.),
       fInnerClad->GetProduct()->GetLogicalVolume(),
      "Clad1PV",
       fOuterClad->GetProduct()->GetLogicalVolume(),
       false,
       0,
       true);
                   
  new G4PVPlacement(0,
      G4ThreeVector(0.,0.,0.),
      fOuterClad->GetProduct()->GetLogicalVolume(),
      "Clad2PV",
      pProduct->GetLogicalVolume(),
      false,
      0,
      true);            
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolidGrooveCompBuilder::SetComponentsDimensions(G4ThreeVector& grooveHalfSize)
{
  VComponentBuilder* vc = ComponentBuilderStore::GetInstance()->GetBuilder("SolidUnit");
  G4Box* solidUnit      = (G4Box*)vc->GetProduct()->GetSolid();
  
	G4double gapThickness = 1*mm;

	if(pPlacedAxis ==NuSDAxisType::eXAxis)
	{ //fiber extends along x direction. put center of fiber on the z axis.
	  
    fCore->SetXHalfLength(solidUnit->GetXHalfLength());
	  
	  fInnerClad->SetXHalfLength(fCore->GetXHalfLength());
	  fInnerClad->SetYHalfLength(fCore->GetYHalfLength()+fInnerCladThickness);
	  fInnerClad->SetZHalfLength(fCore->GetZHalfLength()+fInnerCladThickness);
	  
	  fOuterClad->SetXHalfLength(fCore->GetXHalfLength());
	  fOuterClad->SetYHalfLength(fInnerClad->GetYHalfLength()+0.5*fOutherCladThickness);
	  fOuterClad->SetZHalfLength(fInnerClad->GetZHalfLength()+0.5*fOutherCladThickness);
	  
	  grooveHalfSize = G4ThreeVector(fCore->GetXHalfLength(),
                                   fOuterClad->GetYHalfLength()  + 0.5*gapThickness, 
                                   fOuterClad->GetZHalfLength()  + 0.5*gapThickness
                                   );
            
	}else if(pPlacedAxis == NuSDAxisType::eYAxis)
	{
	  fCore->SetYHalfLength(solidUnit->GetYHalfLength());
	  
	  fInnerClad->SetXHalfLength(fCore->GetXHalfLength()+fInnerCladThickness);
	  fInnerClad->SetYHalfLength(fCore->GetYHalfLength());
	  fInnerClad->SetZHalfLength(fCore->GetZHalfLength()+fInnerCladThickness);
	  
	  fOuterClad->SetXHalfLength(fInnerClad->GetXHalfLength()+0.5*fOutherCladThickness);
	  fOuterClad->SetYHalfLength(fCore->GetYHalfLength());
	  fOuterClad->SetZHalfLength(fInnerClad->GetZHalfLength()+0.5*fOutherCladThickness);
	  
	  grooveHalfSize = G4ThreeVector(fOuterClad->GetXHalfLength()+0.5*gapThickness,
                                   fCore->GetYHalfLength(), 
                                   fOuterClad->GetZHalfLength()+0.5*gapThickness
                                   );
	
	}else if(pPlacedAxis == NuSDAxisType::eZAxis)
	{ //fiber extends along z direction, put center of fiber on the z axis.

	  fCore->SetZHalfLength(solidUnit->GetZHalfLength());
	  	  
	  fInnerClad->SetXHalfLength(fCore->GetXHalfLength()+fInnerCladThickness);
	  fInnerClad->SetYHalfLength(fCore->GetYHalfLength()+fInnerCladThickness);
	  fInnerClad->SetZHalfLength(fCore->GetZHalfLength());
	  
	  fOuterClad->SetXHalfLength(fInnerClad->GetXHalfLength()+0.5*fOutherCladThickness);
	  fOuterClad->SetYHalfLength(fInnerClad->GetYHalfLength()+0.5*fOutherCladThickness);
	  fOuterClad->SetZHalfLength(fCore->GetZHalfLength());
	  
	  grooveHalfSize = G4ThreeVector(fOuterClad->GetXHalfLength()  + 0.5*gapThickness, 
                                   fOuterClad->GetYHalfLength()  + 0.5*gapThickness,
                                   fCore->GetZHalfLength()
                                   );   
	}
	  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

