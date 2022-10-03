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


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NuSDPmtROUnitPlacer_h
#define NuSDPmtROUnitPlacer_h 1

#include "NuSDVROUnitPlacer.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class NuSDVROUnitCompBuilder;
class NuSDVGrooveCompBuilder;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDPmtROUnitPlacer : public NuSDVROUnitPlacer {

  public:
    NuSDPmtROUnitPlacer(); 
    virtual ~NuSDPmtROUnitPlacer();
    
    virtual void Place(const G4VPhysicalVolume* detectorUnit, NuSDVROUnitCompBuilder* readoutUnit) override;
    virtual void Place(const G4VPhysicalVolume*, 
                       const NuSDVGrooveCompBuilder*, 
                       NuSDVROUnitCompBuilder* 
                       ) override{};
                       
  private:
    G4ThreeVector GetROUnitPos(const G4VPhysicalVolume* detectorUnit, 
                               const NuSDVROUnitCompBuilder* readoutUnit 
                              );                       
};

#endif

