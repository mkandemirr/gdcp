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

#include "TrdComponentBuilder.hh"
#include "TrdComponentBuilderMessenger.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Trd.hh"
#include "SmartComponent.hh"
#include "VMaterialFactory.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrdComponentBuilder::TrdComponentBuilder (const G4String &name, 
                                          const G4String& matName, 
                                          VMaterialFactory* matFactory,
                                          G4double pdx1, 
                                          G4double pdx2, 
                                          G4double pdy1, 
                                          G4double pdy2, 
                                          G4double pdz,
                                          G4bool sensitive
                                         ) 
:VComponentBuilder(name, matName, sensitive),
fMessenger{nullptr},
fSolid{nullptr},
fLogic{nullptr},
fMatFactory{matFactory},
fDx1{pdx1},
fDx2{pdx2},
fDy1{pdy1},
fDy2{pdy2},
fDz{pdz}               
{
  fMessenger = new TrdComponentBuilderMessenger(this);
  pProduct   = new SmartComponent(pName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrdComponentBuilder::~TrdComponentBuilder()
{
  if(fMessenger) delete fMessenger;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrdComponentBuilder::CreateMaterial()
{
  if(!pMaterial)
    pMaterial = fMatFactory->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrdComponentBuilder::Construct()
{  
  CreateMaterial();                    
  fSolid  = new G4Trd (pName+"Solid", fDx1, fDx2, fDy1, fDy2, fDz);                                
  fLogic  = new G4LogicalVolume(fSolid, pMaterial, pName+"Logic",0,0,0);
  pProduct->SetLogicalVolume(fLogic);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void 	TrdComponentBuilder::SetXHalfLength1 (G4double val)
{
  fDx1 = val;
  if(fSolid) fSolid->SetXHalfLength1(val);
} 
void 	TrdComponentBuilder::SetXHalfLength2 (G4double val)
{
  fDx2 = val;
  if(fSolid) fSolid->SetXHalfLength2(val);
} 
void 	TrdComponentBuilder::SetYHalfLength1 (G4double val)
{
  fDy1 = val;
  if(fSolid) fSolid->SetYHalfLength1(val);
}
void 	TrdComponentBuilder::SetYHalfLength2 (G4double val)
{
  fDy2 = val;
  if(fSolid) fSolid->SetYHalfLength2(val);
} 

void 	TrdComponentBuilder::SetZHalfLength (G4double val)
{
  fDz = val;
  if(fSolid) fSolid->SetZHalfLength(val);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


