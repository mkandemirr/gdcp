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

#include "NuSDNeutronScntCompBuilder.hh"
//#include "NuSDNeutronScntCompBuilderMessenger.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "SmartComponent.hh"
#include "NuSDNeutronScntSD.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "NuSDMaterialFactory.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDNeutronScntCompBuilder::NuSDNeutronScntCompBuilder(const G4String& name, const G4String& matName, 
                                           G4double dx, G4double dy, G4double dz,
                                           G4bool sensitive
                                           ) 
:BoxComponentBuilder(name, matName, NuSDMaterialFactory::GetInstance(), dx, dy, dz, sensitive)
//fMessenger{nullptr},
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDNeutronScntCompBuilder::~NuSDNeutronScntCompBuilder()
{
  //if(fMessenger) delete fMessenger;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDNeutronScntCompBuilder::ConstructSDAndField()
{
   //---------NeutrinoSD--------------  
  if(!fNeutronSD.Get())
  {
    NuSDNeutronScntSD *mainSD = new NuSDNeutronScntSD(pName+"SD");       
    G4SDManager::GetSDMpointer()->AddNewDetector(mainSD);
    fNeutronSD.Put(mainSD);   
  }

  
  pProduct->GetLogicalVolume()->SetSensitiveDetector(fNeutronSD.Get());
  //SetSensitiveDetector("NeutrinoScntLogic", fNeutronSD.Get(), false);
  //SetSensitiveDetector(fNuScntLogic,fNeutronSD.Get());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




