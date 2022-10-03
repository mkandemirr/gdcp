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

#include "AluminizedMylarMatBuilder.hh"

#include "G4Material.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialBuilderStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AluminizedMylarMatBuilder::AluminizedMylarMatBuilder(const G4String& name, G4bool enableMatProp):
VMaterialBuilder(name,enableMatProp) 
{
  if(enableMatProp)
  {
    G4UImanager* uImanager = G4UImanager::GetUIpointer();
    uImanager->ApplyCommand("/control/execute macros/matPropTable/"+name+".mac");
    
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AluminizedMylarMatBuilder::~AluminizedMylarMatBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* AluminizedMylarMatBuilder::CreateMaterial()          
{ 
  G4double density = 1.40*g/cm3;
  G4int nElements  = 4;
  
  G4Material *aluWrap_mat = new G4Material("AluminizedMylar", density, nElements);
  aluWrap_mat->AddMaterial(pNistManager->FindOrBuildMaterial("G4_H"),  0.03);
  aluWrap_mat->AddMaterial(pNistManager->FindOrBuildMaterial("G4_C"),  0.63);
  aluWrap_mat->AddMaterial(pNistManager->FindOrBuildMaterial("G4_O"),  0.32);
  aluWrap_mat->AddMaterial(pNistManager->FindOrBuildMaterial("G4_Al"), 0.02);
  
  return aluWrap_mat;
}

