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

#include "MaterialPropertiesHelper.hh"
#include "MaterialPropertiesHelperMessenger.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "FileManager.hh"
#include "G4OpticalParameters.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesHelper::MaterialPropertiesHelper(const G4String& name) : 
G4MaterialPropertiesTable(),
fMessenger{nullptr},
fFileManager{FileManager::GetInstance()},
fEnergyVec(),
fValVec(),
fName{name}
{
  fMessenger = new MaterialPropertiesHelperMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesHelper::~MaterialPropertiesHelper()
{
  if(fMessenger) delete fMessenger;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialPropertiesHelper::AddPropertiesToMaterial(G4Material* mat)
{
  G4cout<<fName<<" G4MaterialPropertiesTable---------"<<G4endl;
  G4MaterialPropertiesTable::DumpTable();

  mat->SetMaterialPropertiesTable(this);
  
}

void MaterialPropertiesHelper::AddPropertiesToSurface(G4OpticalSurface* optSurface)
{
  G4cout<<fName<<" G4MaterialPropertiesTable---------"<<G4endl;
  G4MaterialPropertiesTable::DumpTable();

  optSurface->SetMaterialPropertiesTable(this);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialPropertiesHelper::ClearVectors()
{
  fEnergyVec.clear();
  fValVec.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialPropertiesHelper::AddProperty(const G4String& key, const G4String& path)
{ 
  if(key=="ABSLENGTH" || key == "WLSABSLENGTH")
    fFileManager->ReadSpectrumFromFile(path, fEnergyVec, fValVec, 1*eV, 1*cm);
  else
    fFileManager->ReadSpectrumFromFile(path, fEnergyVec, fValVec, 1*eV);
    //unitless time-dependent property, such as refIndex, emission spectrum..
      
  G4MaterialPropertiesTable::AddProperty(key, fEnergyVec, fValVec);
  ClearVectors(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void MaterialPropertiesHelper::AddProperty(const G4String& key, const G4String& path, G4double value)
{
  fFileManager->ReadSpectrumFromFile(path, fEnergyVec, 1*eV); 
  fValVec.insert(fValVec.end(), fEnergyVec.size(), value); 
  
  G4MaterialPropertiesTable::AddProperty(key, fEnergyVec, fValVec);
  ClearVectors(); 
}

