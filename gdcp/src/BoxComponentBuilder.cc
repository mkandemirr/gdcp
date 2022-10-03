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

#include "BoxComponentBuilder.hh"
#include "BoxComponentBuilderMessenger.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "SmartComponent.hh"
#include "VMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BoxComponentBuilder::BoxComponentBuilder(const G4String& name, 
                                         const G4String& matName,
                                         VMaterialFactory* matFactory, 
                                         G4double dx, 
                                         G4double dy, 
                                         G4double dz,
                                         G4bool pSensitive 
                                         ) 
:VComponentBuilder(name, matName, pSensitive),
fMessenger{nullptr},
fSolid{nullptr},
fLogic{nullptr},
fMatFactory{matFactory},
fDx{dx},
fDy{dy},  
fDz{dz}                
{
  fMessenger = new BoxComponentBuilderMessenger(this); 
  pProduct   = new SmartComponent(pName); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BoxComponentBuilder::~BoxComponentBuilder()
{
  if(fMessenger) delete fMessenger;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BoxComponentBuilder::CreateMaterial()
{
  if(!pMaterial)
    pMaterial = fMatFactory->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BoxComponentBuilder::Construct()
{
  CreateMaterial();      
  fSolid  = new G4Box (pName+"Solid", fDx, fDy, fDz);
  fLogic  = new G4LogicalVolume(fSolid, pMaterial, pName+"Logic", 0,0,0);
  
  pProduct->SetLogicalVolume(fLogic);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BoxComponentBuilder::SetXHalfLength(G4double dx)
{
  fDx = dx;
  if(fSolid) fSolid->SetXHalfLength(dx);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BoxComponentBuilder::SetYHalfLength(G4double dy)
{
  fDy = dy;
  if(fSolid) fSolid->SetYHalfLength(dy);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BoxComponentBuilder::SetZHalfLength(G4double dz)
{
  fDz = dz;
  if(fSolid) fSolid->SetZHalfLength(dz);
  
}

