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

#ifndef NuSDVROUnitCompBuilder_h
#define NuSDVROUnitCompBuilder_h 1

#include "VMultiComponentBuilder.hh"
#include "NuSDAxisType.hh"

class GeometryManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDVROUnitCompBuilder : public VMultiComponentBuilder {

  public:
    NuSDVROUnitCompBuilder(const G4String& name, const G4String& matName, NuSDAxisType placedAxis); 
    virtual ~NuSDVROUnitCompBuilder();
    
  public:
    NuSDAxisType GetPlacedAxis() const { return pPlacedAxis;}
 
  protected:
    NuSDAxisType pPlacedAxis;
    GeometryManager* pGeometryManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

