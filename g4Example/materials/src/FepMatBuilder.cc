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

#include "FepMatBuilder.hh"

#include "G4Material.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialBuilderStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FepMatBuilder::FepMatBuilder(const G4String& name, G4bool enableMatProp):
VMaterialBuilder(name, enableMatProp) 
{ 
  if(enableMatProp)
  {
    G4UImanager* uImanager = G4UImanager::GetUIpointer();
    uImanager->ApplyCommand("/control/execute macros/matPropTable/"+name+".mac");
    
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FepMatBuilder::~FepMatBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* FepMatBuilder::CreateMaterial()          
{ 
  //Fluorinated ethylene propylene(FEP) was invented by DuPont and is sold under the brandname Teflon FEP. 
  //This material is used in PROSPECT experiment. The same material composition with G4_Teflon
  G4double density = 2.15*g/cm3; 
  G4int nElements = 2;
  
  G4Material *fep_mat = new G4Material(pName, density, nElements);
  fep_mat->AddElement(pNistManager->FindOrBuildElement("C"), 2);
  fep_mat->AddElement(pNistManager->FindOrBuildElement("F"), 4);
  return fep_mat;
}

