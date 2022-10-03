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

#ifndef MaterialPropertiesHelper_h
#define MaterialPropertiesHelper_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4MaterialPropertiesTable.hh"

class FileManager;
class G4Material;
class G4OpticalSurface;
class MaterialPropertiesHelperMessenger;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MaterialPropertiesHelper: public G4MaterialPropertiesTable {

  public:
    MaterialPropertiesHelper(const G4String& name); 
    virtual ~MaterialPropertiesHelper();
     
  private:
    void ClearVectors();
    
  public:    
    void AddProperty(const G4String& key, const G4String& path);
    void AddProperty(const G4String& key, const G4String& path, G4double value);
    
    void AddPropertiesToMaterial(G4Material *mat);
    void AddPropertiesToSurface(G4OpticalSurface *optSurface);
  
  public:
    //Getters  
    const G4String& GetName() {return fName;}
       
  private:
    MaterialPropertiesHelperMessenger *fMessenger;
    FileManager *fFileManager;
    
    std::vector<G4double> fEnergyVec;
    std::vector<G4double> fValVec;
    
    G4String fName;
    
                  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


