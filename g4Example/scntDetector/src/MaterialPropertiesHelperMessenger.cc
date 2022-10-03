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

#include "MaterialPropertiesHelperMessenger.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4StateManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh" 
//#include "G4UIcmdWithAString.hh"
//#include "G4UIcmdWithADoubleAndUnit.hh"

#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UnitsTable.hh"
 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesHelperMessenger::MaterialPropertiesHelperMessenger(MaterialPropertiesHelper* helper )
 : G4UImessenger(), fHelper{helper}
{
  G4cout<<"MaterialPropertiesHelperMessenger <<"<<fHelper->GetName()<<">> has been created at ";
  G4cout<<G4StateManager::GetStateManager()->GetCurrentState()<<" state..."<<G4endl;
   
  G4String folderName = "/matPropTable/";
  G4String commonName = folderName+fHelper->GetName()+"/";
  
  G4UIparameter* para = nullptr;
  //----------------------------------------------
  G4String name = commonName+"addProperty";
  addPropertyCmd = new G4UIcommand(name,this);
  addPropertyCmd->SetGuidance("Set the the energy-dependent property");
  addPropertyCmd->SetGuidance(" [usage] /materialProperty/addPropert key path value unit ");
  
  para = new G4UIparameter("key",'s',false);
  addPropertyCmd->SetParameter(para);
  para = new G4UIparameter("path",'s',false);
  addPropertyCmd->SetParameter(para);
  para = new G4UIparameter("properyValue",'d',true);
  addPropertyCmd->SetParameter(para);
  addPropertyCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  para = new G4UIparameter("unit",'s',true);
  addPropertyCmd->SetParameter(para);
  addPropertyCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  
  //----------------------------------------------
  name = commonName+"addConstProperty";
  addConstPropertyCmd = new G4UIcommand(name,this);
  addConstPropertyCmd->SetGuidance("Set material const property");
  addConstPropertyCmd->SetGuidance("[usage] /materialProperty/addConstProperty key value unit");
  
  para = new G4UIparameter("key",'s',false);
  addConstPropertyCmd->SetParameter(para);
  para = new G4UIparameter("properyValue",'d',false);
  addConstPropertyCmd->SetParameter(para);
  addConstPropertyCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  //addConstPropertyCmd->SetToBeBroadcasted(false);
  //addConstPropertyCmd->SetToBeBroadcasted(false);
  para = new G4UIparameter("unit",'s',true);
  addConstPropertyCmd->SetParameter(para);
  addConstPropertyCmd->AvailableForStates(G4State_PreInit,G4State_Init);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesHelperMessenger::~MaterialPropertiesHelperMessenger()
{
   delete addConstPropertyCmd;
   delete addPropertyCmd;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Tokenizer.hh"
void MaterialPropertiesHelperMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
 
  if(command==addPropertyCmd)
  {
    G4Tokenizer next(newValue);
    G4String key    = next();
    G4String path   = next();
    G4String value  = next();
    G4String unit   = next();
    G4double dValue = StoD(value);
    
    if(value.empty()){ //two arguments,depends energy
      fHelper->AddProperty(key,path);
    }else if( unit.empty() ){ //three arguments without unit
      fHelper->AddProperty(key, path, dValue);  
    }else if( !(G4UnitDefinition::IsUnitDefined(unit)) ){ //four arguments
      G4ExceptionDescription ed;
      ed << "Unknown unit <" << unit << ">. Command failed.";
      command->CommandFailed(ed);
      
    }else{
      G4String r = value + " " + unit;
      fHelper->AddProperty(key, path, addPropertyCmd->ConvertToDimensionedDouble(r));  
    }
    
  }else if(command==addConstPropertyCmd)
  { 
    G4Tokenizer next(newValue);
    G4String key    = next();
    G4String value  = next();
    G4String unit   = next();
    G4double dValue = StoD(value);

    if(unit.empty()){
      fHelper->AddConstProperty(key,dValue);
    }else if(unit=="1./MeV"){
      fHelper->AddConstProperty(key, dValue*(1./MeV));  
    }else if( unit != "1./MeV" && !(G4UnitDefinition::IsUnitDefined(unit)) ){
      G4ExceptionDescription ed;
      ed << "Unknown unit <" << unit << ">. Command failed.";
      command->CommandFailed(ed);
      
    }else{
      G4String r = value + " " + unit;
      fHelper->AddConstProperty(key,addConstPropertyCmd->ConvertToDimensionedDouble(r));  
    }
   
  
  }
  
}




