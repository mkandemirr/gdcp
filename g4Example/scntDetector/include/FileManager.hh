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

#ifndef FileManager_h
#define FileManager_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "globals.hh"
#include <vector>

//singleton class
class FileManager
{
  public:
    virtual ~FileManager();
    
    static FileManager* GetInstance();

  public:
    void ReadSpectrumFromFile(const G4String &filename, std::vector<G4double> &quantity);
    void ReadSpectrumFromFile(const G4String &filename, std::vector<G4double> &quantity, G4double unit);
    void ReadSpectrumFromFile(const G4String &filename, 
                              std::vector<G4double> &photonEnergy, 
                              std::vector<G4double> &value, 
                              G4double unit1=1., 
                              G4double unit2=1.
                              );	
  private:
    // Private constructor, no objects can be created.
    FileManager();     
  
  private:
    static FileManager* fInstance;  

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 
