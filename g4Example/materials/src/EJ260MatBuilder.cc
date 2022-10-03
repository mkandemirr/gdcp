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

#include "EJ260MatBuilder.hh"

#include "G4Material.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialBuilderStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ260MatBuilder::EJ260MatBuilder(const G4String& name):
VMaterialBuilder(name) 
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ260MatBuilder::~EJ260MatBuilder()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* EJ260MatBuilder::CreateMaterial()          
{
  G4double HydrogenAtomDensity, CarbonAtomDensity;
  G4double HydrogenMassDensity, CarbonMassDensity;
  G4double HydrogenMassFraction,CarbonMassFraction;
  
  G4double a, density;
  G4int nelements;  
  
  //Compounds are defined by mass fractions 
  HydrogenAtomDensity       = 5.21e+22;
  CarbonAtomDensity         = 4.70e+22;

  HydrogenMassDensity       = ConvertAtomDensityToMassDensity(HydrogenAtomDensity, a=1.00794);
  CarbonMassDensity         = ConvertAtomDensityToMassDensity(CarbonAtomDensity, a=12.0107);
  //G4cout<<"Hyrogen Mass density: "<<CarbonMassDensity/(g/cm*cm*cm)<<G4endl;

  HydrogenMassFraction      = HydrogenMassDensity/(HydrogenMassDensity+CarbonMassDensity);
  CarbonMassFraction        = CarbonMassDensity/(HydrogenMassDensity+CarbonMassDensity);
  
  density                   = HydrogenMassDensity+CarbonMassDensity;
  //G4cerr<<"Ej-260 Scintilator density: "<<density/(g/cm3); //gives 1.024 as expected.

  G4Material *scin_mat = new G4Material(pName, density=1.023*g/cm3, nelements=2);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("H"), HydrogenMassFraction);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("C"), CarbonMassFraction);
  
  return scin_mat;  
}

