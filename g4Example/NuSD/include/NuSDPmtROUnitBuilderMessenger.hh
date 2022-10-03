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

#ifndef NuSDPmtROUnitBuilderMessenger_h
#define NuSDPmtROUnitBuilderMessenger_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4UImessenger.hh"

class NuSDPmtROUnitBuilder;
class G4UIdirectory;
class G4UIcmdWithABool;


/*
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
*/
class NuSDPmtROUnitBuilderMessenger: public G4UImessenger
{
  public:
    NuSDPmtROUnitBuilderMessenger(NuSDPmtROUnitBuilder* );
  
  virtual ~NuSDPmtROUnitBuilderMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    NuSDPmtROUnitBuilder *fROUnit;
    //G4UIdirectory      *fDirectory;
    
    G4UIcmdWithABool   *bLightGuideBinderCmd;
    G4UIcmdWithABool   *bLightGuideCmd;
    G4UIcmdWithABool   *bPhotoSensorBinderCmd;
    G4UIcmdWithABool   *bReflectorSurfCmd;
                   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
