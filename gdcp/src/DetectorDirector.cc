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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorDirector.hh"
#include "VMultiComponentBuilder.hh"
#include "SmartComponent.hh"
#include "ComponentBuilderStore.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorDirector::DetectorDirector(VMultiComponentBuilder* detBuilder): 
fDetBuilder{detBuilder}
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorDirector::~DetectorDirector()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorDirector::Initialize()
{
  fDetBuilder->CreateSubComponentBuilders();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SmartComponent* DetectorDirector::MakeDetector()
{
  fDetBuilder->Construct();
  fDetBuilder->PlaceSubComponents();
  return fDetBuilder->GetProduct();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorDirector::ConstructSD()
{
  ComponentBuilderStore* store = ComponentBuilderStore::GetInstance();

  for(auto pos=store->cbegin(); pos!=store->cend(); ++pos)
  {
    if((*pos)->IsSensitive())
    {
      G4cout<<"Sensitive detector <<"<<(*pos)->GetName()<<">> has been created."<<G4endl;
      (*pos)->ConstructSDAndField();
      
    }
    
  }
}

