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

#ifndef DetectorDirector_h
#define DetectorDirector_h 1

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

class SmartComponent;
class VMultiComponentBuilder;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorDirector{

  public:
    DetectorDirector(VMultiComponentBuilder* builder);
    ~DetectorDirector();

    void SetDetBuilder(VMultiComponentBuilder* builder) {fDetBuilder = builder;}
    void Initialize();
    
    SmartComponent* MakeDetector();
    void ConstructSD();
    
  private:
    VMultiComponentBuilder* fDetBuilder;

};

#endif

