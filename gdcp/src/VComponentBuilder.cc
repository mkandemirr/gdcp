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

#include "VComponentBuilder.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "ComponentBuilderStore.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VComponentBuilder::VComponentBuilder(const G4String& name, const G4String& matName, G4bool sensitive) : 
pName{name},
pMatName{matName},
pMaterial{nullptr},
pProduct{nullptr},
bSensitive{sensitive}
{
  ComponentBuilderStore::Register(this);  
  G4cout<<"Component builder <<"<<this->GetName()<<">> has been created."<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VComponentBuilder::~VComponentBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void VComponentBuilder::SetName(const G4String& name)          
{ 
  pName = name;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void VComponentBuilder::SetMaterialName(const G4String& matName)          
{ 
  pMatName = matName;
}

