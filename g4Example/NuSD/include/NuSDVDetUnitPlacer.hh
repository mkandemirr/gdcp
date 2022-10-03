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


/*
Class description:
When construction a detector component, some information 
such as logical and physical volume are saved.

*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#ifndef NuSDVDetUnitPlacer_h
#define NuSDVDetUnitPlacer_h 1

#include "NuSDVDetUnitPlacer.hh"

class GeometryManager;
class SmartComponent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDVDetUnitPlacer {

  public:
    NuSDVDetUnitPlacer(); 
    virtual ~NuSDVDetUnitPlacer();
    
    virtual void Place(SmartComponent* detUnit)=0;
    
  protected:  
    GeometryManager* pGeometryManager;
 
};

#endif

