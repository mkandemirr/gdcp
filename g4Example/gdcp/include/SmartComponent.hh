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

#ifndef SmartComponent_h
#define SmartComponent_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"

class G4LogicalVolume;
class G4VSolid;
class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SmartComponent {

  public:
    SmartComponent(const G4String& name); 
    virtual ~SmartComponent();
                  
    void SetLogicalVolume(G4LogicalVolume* logic)       { fLogic=logic; } 
    void SetPhysicalVolume(G4VPhysicalVolume* physVol)  { fPV = physVol;}       
    std::vector<G4VPhysicalVolume*>& GetPlacementList() { return fPlacementList; } //for more than one placement
   
    const G4String&     GetName()           const { return fName; } 
    G4LogicalVolume*    GetLogicalVolume()  const { return fLogic; }
    G4VSolid*           GetSolid()          const { return fLogic->GetSolid(); }
    G4VPhysicalVolume*  GetPhysicalVolume() const { return fPV; } //for single placement
     
    private:  
      G4String fName;
      G4LogicalVolume*    fLogic;   
      G4VPhysicalVolume*  fPV; //this can be used for component that placed only once.
      std::vector<G4VPhysicalVolume*> fPlacementList;
              
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

