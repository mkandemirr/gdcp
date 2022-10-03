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

#include "TubsComponentBuilder.hh"
#include "TubsComponentBuilderMessenger.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "SmartComponent.hh"
#include "VMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TubsComponentBuilder::TubsComponentBuilder(const G4String& name, 
                                           const G4String& matName, 
                                           VMaterialFactory* matFactory,
                                           G4double pRmin, 
                                           G4double pRMax, 
                                           G4double pDz, 
                                           G4double pSPhi, 
                                           G4double pDPhi,
                                           G4bool pSensitive
                                          ) 
:VComponentBuilder(name, matName, pSensitive),
fMessenger{nullptr},
fSolid{nullptr},
fLogic{nullptr},
fMatFactory{matFactory},
fInnerRadius{pRmin},
fOuterRadius{pRMax},
fZHalfLength{pDz},
fStartPhiAngle{pSPhi},
fDeltaPhiAngle{pDPhi}

{
  fMessenger  = new TubsComponentBuilderMessenger(this);
  pProduct    = new SmartComponent(pName); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TubsComponentBuilder::~TubsComponentBuilder()
{ 
  if(fMessenger) delete fMessenger; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TubsComponentBuilder::CreateMaterial()
{
  if(!pMaterial)
    pMaterial = fMatFactory->FindOrCreateMaterial(pMatName);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TubsComponentBuilder::Construct()
{
  CreateMaterial();  
  fSolid   = new G4Tubs(pName+"Solid", fInnerRadius, fOuterRadius, fZHalfLength, fStartPhiAngle, fDeltaPhiAngle); 
  fLogic   = new G4LogicalVolume(fSolid, pMaterial, pName+"Logic",0,0,0); 
  pProduct->SetLogicalVolume(fLogic);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TubsComponentBuilder::SetInnerRadius(G4double pRMin)
{
  fInnerRadius = pRMin;
  if(fSolid) fSolid->SetInnerRadius(pRMin);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TubsComponentBuilder::SetOuterRadius(G4double pRMax)
{
  fOuterRadius = pRMax;
  if(fSolid) fSolid->SetOuterRadius(pRMax);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
         
void TubsComponentBuilder::SetZHalfLength(G4double pDz)
{
  fZHalfLength = pDz;
  if(fSolid) fSolid->SetZHalfLength(pDz);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TubsComponentBuilder::SetStartPhiAngle(G4double pSPhi)
{
  fStartPhiAngle = pSPhi;
  if(fSolid) fSolid->SetStartPhiAngle(pSPhi);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void TubsComponentBuilder::SetDeltaPhiAngle(G4double pDPhi)
{
  fDeltaPhiAngle = pDPhi;
  if(fSolid) fSolid->SetDeltaPhiAngle(pDPhi);
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

