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

#ifndef NuSDDetectorBuilderMessenger_h
#define NuSDDetectorBuilderMessenger_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4UImessenger.hh"

class NuSDDetectorBuilder;
class G4UIdirectory;

class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
/*
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

*/
class NuSDDetectorBuilderMessenger: public G4UImessenger
{
  public:
    NuSDDetectorBuilderMessenger(NuSDDetectorBuilder* );
  virtual ~NuSDDetectorBuilderMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    NuSDDetectorBuilder       *fDetBuilder;
      
    G4UIcmdWithAnInteger      *fNumberOfSegmentAlongXCmd;
    G4UIcmdWithAnInteger      *fNumberOfSegmentAlongYCmd;
    G4UIcmdWithAnInteger      *fNumberOfSegmentAlongZCmd;
    
    G4UIcmdWithABool          *bROUnitXCmd;
    G4UIcmdWithABool          *bROUnitYCmd;
    G4UIcmdWithABool          *bROUnitZCmd;
    
    G4UIcmdWithABool          *bROUnitXBothEndCmd;
    G4UIcmdWithABool          *bROUnitYBothEndCmd;
    G4UIcmdWithABool          *bROUnitZBothEndCmd;
    
    G4UIcmdWithAString        *ePhotoSensorTypeCmd; 
    
                
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
