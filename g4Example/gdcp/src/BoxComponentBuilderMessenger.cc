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

#include "BoxComponentBuilderMessenger.hh"
#include "BoxComponentBuilder.hh"

#include "G4StateManager.hh"
#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BoxComponentBuilderMessenger::BoxComponentBuilderMessenger(BoxComponentBuilder* box)
 : G4UImessenger(), fBox(box)
{
  G4cout<<"BoxComponentBuilderMessenger <<"<<box->GetName()<<">> has been created at ";
  G4cout<<G4StateManager::GetStateManager()->GetCurrentState()<<" state..."<<G4endl;
  
  G4String folderName = "/NuSD/boxComponent/";
  G4String commonName = folderName+fBox->GetName()+"/";
  
  G4String name = commonName+"xHalfLength";
  fDxCmd = new G4UIcmdWithADoubleAndUnit(name,this);
  fDxCmd->SetGuidance("Set the half size of x");
  fDxCmd->SetParameterName("xHalfLength",false);
  fDxCmd->SetDefaultUnit("cm");
  fDxCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDxCmd->SetToBeBroadcasted(false);
  
  name = commonName+"yHalfLength";
  fDyCmd = new G4UIcmdWithADoubleAndUnit(name,this);
  fDyCmd->SetGuidance("Set the half size of y");
  fDyCmd->SetParameterName("yHalfLength",false);
  fDyCmd->SetDefaultUnit("cm");
  fDyCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDyCmd->SetToBeBroadcasted(false);
  
  name = commonName+"zHalfLength";
  fDzCmd = new G4UIcmdWithADoubleAndUnit(name,this);
  fDzCmd->SetGuidance("Set the half size of z");
  fDzCmd->SetParameterName("zHalfLength",false);
  fDzCmd->SetDefaultUnit("cm");
  fDzCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDzCmd->SetToBeBroadcasted(false);
  
  name = commonName+"matName";
  fMatNameCmd = new G4UIcmdWithAString(name,this);
  fMatNameCmd->SetGuidance("Set the material name");
  fMatNameCmd->SetParameterName("materialName",false);
  fMatNameCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fMatNameCmd->SetToBeBroadcasted(false);
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BoxComponentBuilderMessenger::~BoxComponentBuilderMessenger()
{
  delete fDxCmd;
  delete fDyCmd;
  delete fDzCmd;
  
  delete fMatNameCmd; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BoxComponentBuilderMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  
  if( command == fDxCmd )
  {
    G4double dx = fDxCmd->GetNewDoubleValue(newValue); 
    fBox->SetXHalfLength(dx);
  }
  else if( command == fDyCmd )
  {
    G4double dy = fDyCmd->GetNewDoubleValue(newValue); 
    fBox->SetYHalfLength(dy);
  } 
  else if( command == fDzCmd )
  {
    G4double dz = fDzCmd->GetNewDoubleValue(newValue); 
    fBox->SetZHalfLength(dz);
  }
  else if (command == fMatNameCmd)
  {
    
    fBox->SetMaterialName(newValue);
  }   
    
}




