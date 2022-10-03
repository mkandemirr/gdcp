//***********************************************************************
//* Photon Segmented Detector (NuSD) Copyright 2022 Mustafa Kandemir  *
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

#include "NuSDMppcCompBuilder.hh"
//#include "NuSDMppcCompBuilderMessenger.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "SmartComponent.hh"
#include "NuSDPhotonSD.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "NuSDSimManager.hh"
#include "OpticalSurface.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4UImanager.hh"
#include "G4LogicalSkinSurface.hh"
#include "NuSDMaterialFactory.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDMppcCompBuilder::NuSDMppcCompBuilder(const G4String& name, const G4String& matName, 
                                 G4double dx, G4double dy, G4double dz,
                                 G4bool sensitive
                                ) 
:BoxComponentBuilder(name, matName,NuSDMaterialFactory::GetInstance(), dx, dy, dz, sensitive)
//fMessenger{nullptr},
{
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  
  //----
  fPSMatProp = new MaterialPropertiesHelper(pName);
  uImanager->ApplyCommand("/control/execute macros/matPropTable/"+pName+".mac");
  
  fPSSurface = new OpticalSurface(pName);  
  uImanager->ApplyCommand("/control/execute macros/opticalSurface/"+pName+".mac");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDMppcCompBuilder::~NuSDMppcCompBuilder()
{
  //if(fMessenger) delete fMessenger;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDMppcCompBuilder::Construct()
{
  BoxComponentBuilder::Construct();
  SetPrivateSurfaceAndMaterialProperties();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDMppcCompBuilder::ConstructSDAndField()
{
   //---------PhotonSD--------------  
  
  if(NuSDSimManager::GetInstance()->IsOpticalPhysicsOn()) 
  { 
      
    if(!fPhotonSD.Get())
    {    
      NuSDPhotonSD *photonSD = new NuSDPhotonSD(pName+"SD");
      G4SDManager::GetSDMpointer()->AddNewDetector(photonSD); 
      fPhotonSD.Put(photonSD);      
    
    }
  
  } 
  
  pProduct->GetLogicalVolume()->SetSensitiveDetector(fPhotonSD.Get());
  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDMppcCompBuilder::SetPrivateSurfaceAndMaterialProperties()
{
  //Set MPPc
  fPSSurface->SetMaterialPropertiesTable(fPSMatProp);
  new G4LogicalSkinSurface("mppcSkinSurf", pProduct->GetLogicalVolume(), fPSSurface );
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




