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

#ifndef VMaterialBuilder_h
#define VMaterialBuilder_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"

class G4Material;
class MaterialPropertiesHelper;
class G4NistManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class VMaterialBuilder{

  public:
    VMaterialBuilder(const G4String& name, G4bool enableMatProp = false); 
    virtual ~VMaterialBuilder();

    G4Material* GetProduct(); //business logic
    const G4String& GetName() const { return pName; }
    G4bool IsMaterialPropertyOn() {return bEnableMatProp;}
    
  protected:
    virtual G4Material* CreateMaterial() = 0;    
    
    //commonly used members in derived classes
    G4double ConvertAtomDensityToMassDensity(G4double ad, G4double mw);
    G4String pName;
    G4NistManager* pNistManager;
  private:  
    G4bool bEnableMatProp;
    MaterialPropertiesHelper* fMatPropHelper;   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

