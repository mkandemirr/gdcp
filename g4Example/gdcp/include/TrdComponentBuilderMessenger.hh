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

#ifndef TrdComponentBuilderMessenger_h
#define TrdComponentBuilderMessenger_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4UImessenger.hh"

class TrdComponentBuilder;
class G4UIdirectory;

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

class TrdComponentBuilderMessenger: public G4UImessenger
{
  public:
    TrdComponentBuilderMessenger(TrdComponentBuilder* );
  virtual ~TrdComponentBuilderMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    TrdComponentBuilder       *fTrd;
   
    G4UIcmdWithAString        *fMatNameCmd; 
    G4UIcmdWithADoubleAndUnit *fDx1Cmd,*fDx2Cmd,*fDy1Cmd,*fDy2Cmd,*fDzCmd; 
                    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
