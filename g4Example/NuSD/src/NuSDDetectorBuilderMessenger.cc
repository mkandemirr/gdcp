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

#include "NuSDDetectorBuilderMessenger.hh"
#include "NuSDDetectorBuilder.hh"

//#include "G4StateManager.hh"
//#include "G4ApplicationState.hh"
//#include "G4RunManager.hh"
#include "G4StateManager.hh"
//#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
//#include "G4UIcmdWith3VectorAndUnit.hh"
//#include "G4UIcmdWithADoubleAndUnit.hh"
//#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh" 
#include "NuSDPhotoSensorType.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDDetectorBuilderMessenger::NuSDDetectorBuilderMessenger(NuSDDetectorBuilder* detBuilder)
 : G4UImessenger(), fDetBuilder(detBuilder)
{
  G4cout<<detBuilder->GetName()<<" messenger is initializing at ";
  G4cout<<G4StateManager::GetStateManager()->GetCurrentState()<<" state"<<G4endl;
  
  G4String folderName = "/NuSD/";
  G4String commonName = folderName+fDetBuilder->GetName()+"/";
 
  G4String name = commonName+"numberOfSegmentAlongX";  
  fNumberOfSegmentAlongXCmd = new G4UIcmdWithAnInteger(name, this);
  fNumberOfSegmentAlongXCmd->SetGuidance("Number of segment along x" "\n  0 or negative values mean <<Don't change it!>>");
  fNumberOfSegmentAlongXCmd->SetParameterName("numberOfSegmentAlongX", false);
  fNumberOfSegmentAlongXCmd->SetDefaultValue(3);
  fNumberOfSegmentAlongXCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fNumberOfSegmentAlongXCmd->SetToBeBroadcasted(false);
  
  name = commonName+"numberOfSegmentAlongY";
  fNumberOfSegmentAlongYCmd = new G4UIcmdWithAnInteger(name, this);
  fNumberOfSegmentAlongYCmd->SetGuidance("Number of segment along y" "\n  0 or negative values mean <<Don't change it!>>");
  fNumberOfSegmentAlongYCmd->SetParameterName("numberOfSegmentAlongY", false);
  fNumberOfSegmentAlongYCmd->SetDefaultValue(3);
  fNumberOfSegmentAlongYCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fNumberOfSegmentAlongYCmd->SetToBeBroadcasted(false);
  
  name = commonName+"numberOfSegmentAlongZ";
  fNumberOfSegmentAlongZCmd = new G4UIcmdWithAnInteger(name, this);
  fNumberOfSegmentAlongZCmd->SetGuidance("Number of segment along z" "\n  0 or negative values mean <<Don't change it!>>");
  fNumberOfSegmentAlongZCmd->SetParameterName("numberOfSegmentAlongZ", false);
  fNumberOfSegmentAlongZCmd->SetDefaultValue(3);
  fNumberOfSegmentAlongZCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  fNumberOfSegmentAlongZCmd->SetToBeBroadcasted(false);
  
  name = commonName+"photoSensorType";
  ePhotoSensorTypeCmd = new G4UIcmdWithAString(name, this);
  ePhotoSensorTypeCmd->SetGuidance("Select photoSensor type");
  ePhotoSensorTypeCmd->SetParameterName("photoSensorType", false);
  ePhotoSensorTypeCmd->SetCandidates("PMT SiPM");
  ePhotoSensorTypeCmd->SetDefaultValue("SiPM");
  ePhotoSensorTypeCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  ePhotoSensorTypeCmd->SetToBeBroadcasted(false);
  
  name = commonName+"addReadoutUnitX";
  bROUnitXCmd = new G4UIcmdWithABool(name, this);
  bROUnitXCmd->SetGuidance("Add optical readout along x");
  bROUnitXCmd->SetParameterName("opticalROUnitX", false);
  bROUnitXCmd->SetDefaultValue(false);
  bROUnitXCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bROUnitXCmd->SetToBeBroadcasted(false);
  
  name = commonName+"addReadoutUnitY";
  bROUnitYCmd = new G4UIcmdWithABool(name, this);
  bROUnitYCmd->SetGuidance("Add optical readout along y");
  bROUnitYCmd->SetParameterName("opticalROUnitY", false);
  bROUnitYCmd->SetDefaultValue(false);
  bROUnitYCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bROUnitYCmd->SetToBeBroadcasted(false);
  
  name = commonName+"addReadoutUnitZ";
  bROUnitZCmd = new G4UIcmdWithABool(name, this);
  bROUnitZCmd->SetGuidance("Add optical readout along z");
  bROUnitZCmd->SetParameterName("opticalROUnitZ", false);
  bROUnitZCmd->SetDefaultValue(false);
  bROUnitZCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bROUnitZCmd->SetToBeBroadcasted(false);
  
  name = commonName+"addReadoutUnitXBothEnd";
  bROUnitXBothEndCmd = new G4UIcmdWithABool(name, this);
  bROUnitXBothEndCmd->SetGuidance("Add optical readout unit x both end");
  bROUnitXBothEndCmd->SetParameterName("opticalROUnitXBothEnd", false);
  bROUnitXBothEndCmd->SetDefaultValue(false);
  bROUnitXBothEndCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bROUnitXBothEndCmd->SetToBeBroadcasted(false);
  
  name = commonName+"addReadoutUnitYBothEnd";
  bROUnitYBothEndCmd = new G4UIcmdWithABool(name, this);
  bROUnitYBothEndCmd->SetGuidance("Add optical readout unit y both end");
  bROUnitYBothEndCmd->SetParameterName("opticalROUnitYBothEnd", false);
  bROUnitYBothEndCmd->SetDefaultValue(false);
  bROUnitYBothEndCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bROUnitYBothEndCmd->SetToBeBroadcasted(false);
  
  name = commonName+"addReadoutUnitZBothEnd";
  bROUnitZBothEndCmd = new G4UIcmdWithABool(name, this);
  bROUnitZBothEndCmd->SetGuidance("Add optical readout unit z both end");
  bROUnitZBothEndCmd->SetParameterName("opticalROUnitZBothEnd", false);
  bROUnitZBothEndCmd->SetDefaultValue(false);
  bROUnitZBothEndCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  bROUnitZBothEndCmd->SetToBeBroadcasted(false);
  
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDDetectorBuilderMessenger::~NuSDDetectorBuilderMessenger()
{
  //delete fDetBuilderDirectory;
  
  delete fNumberOfSegmentAlongXCmd;
  delete fNumberOfSegmentAlongYCmd;
  delete fNumberOfSegmentAlongZCmd;  
  
  delete ePhotoSensorTypeCmd;
  
  delete bROUnitXCmd;
  delete bROUnitYCmd;
  delete bROUnitZCmd;
  
  delete bROUnitXBothEndCmd;
  delete bROUnitYBothEndCmd;
  delete bROUnitZBothEndCmd;
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilderMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  
  if( command == fNumberOfSegmentAlongXCmd )
  {
    G4int numOfSegmentAlongX = fNumberOfSegmentAlongXCmd->GetNewIntValue(newValue); 
    fDetBuilder->SetNumberOfSegmentAlongX(numOfSegmentAlongX);
    
  }else if( command == fNumberOfSegmentAlongYCmd )  
  {
    G4int numOfSegmentAlongY = fNumberOfSegmentAlongYCmd->GetNewIntValue(newValue); 
    fDetBuilder->SetNumberOfSegmentAlongY(numOfSegmentAlongY);

  } else if( command == fNumberOfSegmentAlongZCmd )
  {
    G4int numOfSegmentAlongZ = fNumberOfSegmentAlongZCmd->GetNewIntValue(newValue); 
    fDetBuilder->SetNumberOfSegmentAlongZ(numOfSegmentAlongZ);

  }else if( command == ePhotoSensorTypeCmd )
  {
    if(newValue=="PMT")
      fDetBuilder->SetPhotoSensorType(NuSDPhotoSensorType::ePMT);
    else if(newValue=="SiPM")
      fDetBuilder->SetPhotoSensorType(NuSDPhotoSensorType::eSiPM);  

  }else if( command == bROUnitXCmd )
  {
    fDetBuilder->SetROUnitXFlag(bROUnitXCmd->GetNewBoolValue(newValue));

  } 
  else if( command == bROUnitYCmd )
  {
    fDetBuilder->SetROUnitYFlag(bROUnitYCmd->GetNewBoolValue(newValue));

  } 
  else if( command == bROUnitZCmd )
  {
    fDetBuilder->SetROUnitZFlag(bROUnitZCmd->GetNewBoolValue(newValue));

  }else if( command == bROUnitXBothEndCmd )
  {
    fDetBuilder->SetROUnitXBothEndFlag(bROUnitXBothEndCmd->GetNewBoolValue(newValue));

  }else if( command == bROUnitYBothEndCmd )
  {
    fDetBuilder->SetROUnitYBothEndFlag(bROUnitYBothEndCmd->GetNewBoolValue(newValue));

  }else if( command == bROUnitZBothEndCmd )
  {
    fDetBuilder->SetROUnitZBothEndFlag(bROUnitZBothEndCmd->GetNewBoolValue(newValue));

  }    
    
}




