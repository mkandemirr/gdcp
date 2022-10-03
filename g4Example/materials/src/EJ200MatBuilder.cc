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

#include "EJ200MatBuilder.hh"
#include "G4Material.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialBuilderStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ200MatBuilder::EJ200MatBuilder(const G4String& name, G4bool enableMatProp):
VMaterialBuilder(name, enableMatProp) 
{
  if(enableMatProp)
  {
    G4UImanager* uImanager = G4UImanager::GetUIpointer();
    uImanager->ApplyCommand("/control/execute macros/matPropTable/"+name+".mac");
    
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ200MatBuilder::~EJ200MatBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* EJ200MatBuilder::CreateMaterial()          
{ 
  G4double hydrogenAtomDensity = 5.17e+22;
  G4double carbonAtomDensity   = 4.69e+22;

  G4double a, density;
  G4int nelements;
  
	G4double hydrogenMassDensity = ConvertAtomDensityToMassDensity(hydrogenAtomDensity,a=1.00794);
	G4double carbonMassDensity 	 = ConvertAtomDensityToMassDensity(carbonAtomDensity, a=12.0107);
	//G4cout<<"Hyrogen Mass density: "<<hydrogenMassDensity/(g/cm*cm*cm)<<G4endl;

	G4double hydrogenMassFraction = hydrogenMassDensity/(hydrogenMassDensity+carbonMassDensity);
	G4double carbonMassFraction 	= carbonMassDensity/(hydrogenMassDensity+carbonMassDensity);

	//density = hydrogenMassDensity+carbonMassDensity;
	//G4cout<<"Ej-200 Scintilator density: "<<density/(g/cm3)<<G4endl;  //gives 1.02 as expected

	G4Material *scin_mat = new G4Material(pName, density=1.023*g/cm3, nelements=2);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("H"), hydrogenMassFraction);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("C"), carbonMassFraction);
   
  return scin_mat;  
}

