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

#ifndef BoxComponentBuilder_h
#define BoxComponentBuilder_h 1

#include "VComponentBuilder.hh"

class BoxComponentBuilderMessenger;
class G4Box;
class VMaterialFactory;
class G4LogicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class BoxComponentBuilder : public VComponentBuilder{

  public:
    BoxComponentBuilder(const G4String& name, 
                        const G4String& matName, 
                        VMaterialFactory* matFactory,
                        G4double dx=0., 
                        G4double dy=0., 
                        G4double dz=0., 
                        G4bool pSensitive = false
                       );                    
    virtual ~BoxComponentBuilder();
    
    virtual void CreateMaterial() override;
    virtual void Construct()  override;
  
  //Getters  
  public:
    G4double GetXHalfLength() const { return fDx; }
    G4double GetYHalfLength() const { return fDy; }
    G4double GetZHalfLength() const { return fDz; }
    
  //Setters
  public:  
    void SetXHalfLength(G4double dx);
    void SetYHalfLength(G4double dy);
    void SetZHalfLength(G4double dz);

  private:
    BoxComponentBuilderMessenger* fMessenger;
    
    G4Box* fSolid;
    G4LogicalVolume* fLogic;
    VMaterialFactory* fMatFactory;
    
    G4double fDx;
    G4double fDy;
    G4double fDz; 
              
};


#endif


