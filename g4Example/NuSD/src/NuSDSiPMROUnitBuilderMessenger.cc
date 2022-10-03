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

#include "NuSDSiPMROUnitBuilderMessenger.hh"
#include "NuSDSiPMROUnitBuilder.hh"

#include "G4StateManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh" 
//#include "G4UIcmdWithAString.hh"
//#include "G4UIcmdWithADoubleAndUnit.hh"
 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSiPMROUnitBuilderMessenger::NuSDSiPMROUnitBuilderMessenger(NuSDSiPMROUnitBuilder* optROUnit )
 : G4UImessenger(), fROUnit{optROUnit}
{
  G4cout<<"Component messenger <<"<<fROUnit->GetName()<<">> has been created at ";
  G4cout<<G4StateManager::GetStateManager()->GetCurrentState()<<" state..."<<G4endl;
  
  G4String folderName = "/NuSD/readout/";
  G4String commonName = folderName+fROUnit->GetName()+"/";
  
  G4String name = commonName+"addPhotoSensorBinder";
  bPhotoSensorBinderCmd = new G4UIcmdWithABool(name, this);
  bPhotoSensorBinderCmd->SetGuidance("Add photosensor binder");
  bPhotoSensorBinderCmd->SetParameterName("PhotoSensorBinder", false);
  bPhotoSensorBinderCmd->SetDefaultValue(false);
  bPhotoSensorBinderCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bPhotoSensorBinderCmd->SetToBeBroadcasted(false);
  
  name = commonName+"addReflectorSurface";
  bReflectorSurfCmd = new G4UIcmdWithABool(name, this);
  bReflectorSurfCmd->SetGuidance("Add reflector surface");
  bReflectorSurfCmd->SetParameterName("ReflectorSurface", false);
  bReflectorSurfCmd->SetDefaultValue(false);
  bReflectorSurfCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bReflectorSurfCmd->SetToBeBroadcasted(false);
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSiPMROUnitBuilderMessenger::~NuSDSiPMROUnitBuilderMessenger()
{
   delete bPhotoSensorBinderCmd;
   delete bReflectorSurfCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDSiPMROUnitBuilderMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == bPhotoSensorBinderCmd )
  {
    fROUnit->SetPhotoSensorBinderFlag(bPhotoSensorBinderCmd->GetNewBoolValue(newValue));

  }else if( command == bReflectorSurfCmd )
  {
    fROUnit->SetReflectorSurfaceFlag(bReflectorSurfCmd->GetNewBoolValue(newValue));

  }
  
}




