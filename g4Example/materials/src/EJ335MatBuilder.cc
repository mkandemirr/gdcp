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

#include "EJ335MatBuilder.hh"

#include "G4Material.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialBuilderStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ335MatBuilder::EJ335MatBuilder(const G4String& name):
VMaterialBuilder(name) 
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ335MatBuilder::~EJ335MatBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4Material* EJ335MatBuilder::CreateMaterial()          
{ 
  G4int ncomponents{0};  
  G4double density = 0.89*g/cm3;
	G4double a;
	
	G4double hydrogenAtomDensity 	= 6.16e+22;
	//carbonAtomDensity 		  = 3.93e+22;
  
	G4double hydrogenMassDensity = ConvertAtomDensityToMassDensity(hydrogenAtomDensity, a=1.00794);
	//carbonMassDensity 		  = ConvertAtomDensityToMassDensity(carbonAtomDensity, a=12.0107);
	
	G4double hydrogenMassFraction = hydrogenMassDensity/density;
	G4double gdMassFraction = 0.25*perCent;
	G4double carbonMassFraction  = 1-gdMassFraction-hydrogenMassFraction;

  G4Element *el_Gd = pNistManager->FindOrBuildElement("Gd");

	G4Material *scin_mat = new G4Material(pName, density, ncomponents=3);
	scin_mat->AddElement(pNistManager->FindOrBuildElement("H"), hydrogenMassFraction);
	scin_mat->AddElement(pNistManager->FindOrBuildElement("C"), carbonMassFraction);
	scin_mat->AddElement(el_Gd, gdMassFraction);
  
  return scin_mat;  
}

