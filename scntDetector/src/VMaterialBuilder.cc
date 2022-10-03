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

#include "VMaterialBuilder.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "MaterialPropertiesHelper.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialBuilder::VMaterialBuilder(const G4String& name, G4bool enableMatProp) : 
pName{name},
pNistManager{G4NistManager::Instance()},
bEnableMatProp{enableMatProp},
fMatPropHelper{nullptr}
{
  G4cout<<"Material builder <<"<<this->GetName()<<">> has been created."<<G4endl;
  
  if(bEnableMatProp)
  {
    fMatPropHelper = new MaterialPropertiesHelper(pName);   
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialBuilder::~VMaterialBuilder()
{ 
  if(fMatPropHelper) delete fMatPropHelper;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* VMaterialBuilder::GetProduct()
{
  G4Material* mat = CreateMaterial();
  
  if(bEnableMatProp)
    fMatPropHelper->AddPropertiesToMaterial(mat);
  
  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double VMaterialBuilder::ConvertAtomDensityToMassDensity(G4double ad, G4double mw)
{

  const G4double N_A          = (6.02e+23)*(1/mole);
  G4double atomDensity        = ad*(1/cm3);
  G4double molecularWeight    = mw*(g/mole);
  G4double massDensity        = (atomDensity/N_A)*molecularWeight;

  return massDensity; // g/cm3

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
