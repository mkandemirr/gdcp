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

#include "TrdComponentBuilderMessenger.hh"
#include "TrdComponentBuilder.hh"

#include "G4StateManager.hh"
#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrdComponentBuilderMessenger::TrdComponentBuilderMessenger(TrdComponentBuilder* trd)
 : G4UImessenger(), fTrd(trd)
{
  G4cout<<"TrdComponentBuilderMessenger <<"<<fTrd->GetName()<<">> has been created at ";
  G4cout<<G4StateManager::GetStateManager()->GetCurrentState()<<" state..."<<G4endl;
  
  G4String folderName = "/NuSD/trdComponent/";
  G4String commonName = folderName+fTrd->GetName()+"/";
  
  G4String name = commonName+"x1HalfLength"; 
  fDx1Cmd = new G4UIcmdWithADoubleAndUnit(name, this);
  fDx1Cmd->SetGuidance("Set x halfLength 1");
  fDx1Cmd->SetParameterName("x1HalfLength", false);
  //fDx1Cmd->SetDefaultValue(1*cm);
  fDx1Cmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDx1Cmd->SetToBeBroadcasted(false); 
  
  name = commonName+"x2HalfLength";
  fDx2Cmd = new G4UIcmdWithADoubleAndUnit(name, this);
  fDx2Cmd->SetGuidance("Set x halfLength 2");
  fDx2Cmd->SetParameterName("x2HalfLength", false);
  //fDx2Cmd->SetDefaultValue(1*cm);
  fDx2Cmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDx2Cmd->SetToBeBroadcasted(false); 
  
  name = commonName+"y1HalfLength";
  fDy1Cmd = new G4UIcmdWithADoubleAndUnit(name, this);
  fDy1Cmd->SetGuidance("Set y halfLength 1");
  fDy1Cmd->SetParameterName("y1HalfLength", false);
  //fDy1Cmd->SetDefaultValue(1*cm);
  fDy1Cmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDy1Cmd->SetToBeBroadcasted(false); 
  
  name = commonName+"y2HalfLength";
  fDy2Cmd = new G4UIcmdWithADoubleAndUnit(name, this);
  fDy2Cmd->SetGuidance("Set y halfLength 2");
  fDy2Cmd->SetParameterName("y2HalfLength", false);
  //fDy2Cmd->SetDefaultValue(1*cm);
  fDy2Cmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDy2Cmd->SetToBeBroadcasted(false);  
    
  name = commonName+"zHalfLength";  
  fDzCmd = new G4UIcmdWithADoubleAndUnit(name, this);
  fDzCmd->SetGuidance("Set z halfLength");
  fDzCmd->SetParameterName("zHalfLength", false);
  //fDzCmd->SetDefaultValue(1*cm);
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

TrdComponentBuilderMessenger::~TrdComponentBuilderMessenger()
{
  delete fDx1Cmd;
  delete fDx2Cmd;
  delete fDy1Cmd;
  delete fDy2Cmd;
  delete fDzCmd;
  
  delete fMatNameCmd;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrdComponentBuilderMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  
  if( command == fDx1Cmd )
  {
    fTrd->SetXHalfLength1(fDx1Cmd->GetNewDoubleValue(newValue));
    
  }else if( command == fDx2Cmd )
  {
    fTrd->SetXHalfLength2(fDx2Cmd->GetNewDoubleValue(newValue));
    
  }else if( command == fDy1Cmd )
  {
    fTrd->SetYHalfLength1(fDy1Cmd->GetNewDoubleValue(newValue));
    
  }
  else if( command == fDy2Cmd )
  {
    fTrd->SetYHalfLength2(fDy2Cmd->GetNewDoubleValue(newValue));
    
  }
  else if( command == fDzCmd )
  {
    fTrd->SetZHalfLength(fDzCmd->GetNewDoubleValue(newValue));
    
  }
  else if (command == fMatNameCmd)
  {
    
    fTrd->SetMaterialName(newValue);
  }   
      
}




