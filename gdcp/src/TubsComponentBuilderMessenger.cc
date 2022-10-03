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

#include "TubsComponentBuilderMessenger.hh"
#include "TubsComponentBuilder.hh"

#include "G4StateManager.hh"
#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TubsComponentBuilderMessenger::TubsComponentBuilderMessenger(TubsComponentBuilder* tubs)
 : G4UImessenger(), fTubs(tubs)
{
  G4cout<<"TubsComponentBuilderMessenger <<"<<fTubs->GetName()<<">> has been created at ";
  G4cout<<G4StateManager::GetStateManager()->GetCurrentState()<<" state"<<G4endl;
  
  G4String folderName = "/NuSD/tubsComponent/";
  G4String commonName = folderName+fTubs->GetName()+"/";
  
  G4String name = commonName+"halfLength";  
  fDzCmd = new G4UIcmdWithADoubleAndUnit(name, this);
  fDzCmd->SetGuidance("Half Length of photosensor binder");
  fDzCmd->SetParameterName("TubsBinderLength", false);
  //fDzCmd->SetDefaultValue(1*cm);
  fDzCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fDzCmd->SetToBeBroadcasted(false);
  
  name = commonName+"matName";
  fMatNameCmd = new G4UIcmdWithAString(name,this);
  fMatNameCmd->SetGuidance("Set the material name");
  fMatNameCmd->SetParameterName("materialName",false);
  fMatNameCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fMatNameCmd->SetToBeBroadcasted(false);
  
  name = commonName+"radius";
  fOuterRadiusCmd = new G4UIcmdWithADoubleAndUnit(name, this);
  fOuterRadiusCmd->SetGuidance("radius");
  fDzCmd->SetParameterName("Radius", false);
  //fOuterRadiusCmd->SetDefaultValue(1*cm);
  fOuterRadiusCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fOuterRadiusCmd->SetToBeBroadcasted(false);
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TubsComponentBuilderMessenger::~TubsComponentBuilderMessenger()
{
  
  delete fDzCmd;
  delete fMatNameCmd;
  delete fOuterRadiusCmd;
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TubsComponentBuilderMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  
  if( command == fDzCmd )
  {
    fTubs->SetZHalfLength(fDzCmd->GetNewDoubleValue(newValue));
    
  }
  else if (command == fMatNameCmd)
  {
    
    fTubs->SetMaterialName(newValue);
  }else if (command == fOuterRadiusCmd)
  {
    
    fTubs->SetOuterRadius(fOuterRadiusCmd->GetNewDoubleValue(newValue));
  }      
      
}




