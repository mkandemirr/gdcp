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

#ifndef VComponentBuilder_h
#define VComponentBuilder_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"
//#include "G4LogicalVolume.hh"

class SmartComponent;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class VComponentBuilder{

  public:
    VComponentBuilder(const G4String& name, const G4String& matName, G4bool sensitive=false); 
    virtual ~VComponentBuilder();

    virtual void CreateMaterial() = 0;
    virtual void Construct()      = 0;
    virtual void ConstructSDAndField() {};
    
    SmartComponent* GetProduct()  {return pProduct;}
    
    //Getters
    const G4String& GetName()         const {return pName; } 
    const G4String& GetMaterialName() const {return pMatName; }
    SmartComponent* GetConstProduct() const {return pProduct;}
    
    G4bool IsSensitive() {return bSensitive;}
    
    inline G4bool operator == (const VComponentBuilder& p) const;
    
    //Setters, for UIcommands
    void SetName(const G4String& name);
    void SetMaterialName(const G4String& name);
  
  protected:
    G4String pName;
    G4String pMatName;
    G4Material* pMaterial;
    SmartComponent* pProduct;
   private: 
    G4bool bSensitive;              
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4bool VComponentBuilder::operator == (const VComponentBuilder& right) const
{
  return (this==&right) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

