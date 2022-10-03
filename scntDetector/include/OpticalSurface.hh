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

#ifndef OpticalSurface_H
#define OpticalSurface_H 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"

class OpticalSurfaceMessenger;

class OpticalSurface: public G4OpticalSurface 
{
  public:
    OpticalSurface(const G4String& name, 
                   G4OpticalSurfaceModel model   = glisur,
                   G4OpticalSurfaceFinish finish = polished,
                   G4SurfaceType type            = dielectric_dielectric,
                   G4double value                = 1.0
                  );
   virtual ~OpticalSurface();
                                              
  private:
    OpticalSurfaceMessenger* fMessenger; 
    G4String fName; 

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
