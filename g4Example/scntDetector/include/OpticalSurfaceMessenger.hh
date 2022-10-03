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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef OpticalSurfaceMessenger_h
#define OpticalSurfaceMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class OpticalSurface;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class OpticalSurfaceMessenger : public G4UImessenger
{
 public:
  OpticalSurfaceMessenger(OpticalSurface*);
  ~OpticalSurfaceMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

 private:
  OpticalSurface* fOptSurface;

  G4UIcmdWithAString* fSurfaceTypeCmd;
  G4UIcmdWithAString* fSurfaceFinishCmd;
  G4UIcmdWithAString* fSurfaceModelCmd;
  G4UIcmdWithADouble* fSurfaceSigmaAlphaCmd;
  G4UIcmdWithADouble* fSurfacePolishCmd;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
