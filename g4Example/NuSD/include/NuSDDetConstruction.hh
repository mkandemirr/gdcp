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

#ifndef NuSDDetConstruction_h
#define NuSDDetConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"

class G4VPhysicalVolume;
class G4Material;
class NuSDGeometryManager;
class NuSDVDetUnitCompBuilder;
class NuSDDetectorBuilder;
class DetectorDirector;
class GeometryManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDDetConstruction : public G4VUserDetectorConstruction
{
  public:
    NuSDDetConstruction(NuSDVDetUnitCompBuilder* detUnitBuilder);
    ~NuSDDetConstruction() override;

    virtual G4VPhysicalVolume* Construct() override;
    virtual void ConstructSDandField() override;
  
  private:
    GeometryManager* pGeometryManager;
    NuSDDetectorBuilder* fDetBuilder;
    DetectorDirector* fDetDirector;
};



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
