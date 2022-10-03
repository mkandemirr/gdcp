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

#ifndef NuSDVROUnitPlacer_h
#define NuSDVROUnitPlacer_h 1

#include "NuSDVROUnitPlacer.hh"

class G4VPhysicalVolume;
class NuSDVROUnitCompBuilder;
class GeometryManager;
class NuSDVGrooveCompBuilder;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDVROUnitPlacer {

  public:
    NuSDVROUnitPlacer(); 
    virtual ~NuSDVROUnitPlacer();
    
    virtual void Place(const G4VPhysicalVolume* detUnit, NuSDVROUnitCompBuilder* readoutUnit)=0;

    virtual void Place(const G4VPhysicalVolume* detUnit, 
                       const NuSDVGrooveCompBuilder* grooveComp, 
                       NuSDVROUnitCompBuilder* readoutUnit
                      )=0;
    
  protected:  
    GeometryManager* pGeometryManager;
 
};

#endif

