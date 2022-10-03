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

#ifndef TrdComponentBuilder_h
#define TrdComponentBuilder_h 1

#include "VComponentBuilder.hh"

class TrdComponentBuilderMessenger;
class G4Trd;
class VMaterialFactory;
class G4LogicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrdComponentBuilder : public VComponentBuilder{

  public:
    TrdComponentBuilder ( const G4String &name, 
                          const G4String& matName, 
                          VMaterialFactory* matFactory,
                          G4double dx1=0., 
                          G4double dx2=0., 
                          G4double dy1=0., 
                          G4double dy2=0., 
                          G4double dz=0.,
                          G4bool sensitive=false
                        );
    virtual ~TrdComponentBuilder();
  
    virtual void CreateMaterial() override;
    virtual void Construct()  override;
  
  //Getters  
  public:    
    G4double 	GetXHalfLength1 () const {return fDx1; }
    G4double 	GetXHalfLength2 () const {return fDx2; }  
    G4double 	GetYHalfLength1 () const {return fDy1; }
    G4double 	GetYHalfLength2 () const {return fDy2; }
    G4double 	GetZHalfLength ()  const {return fDz; }
 
  //Setters
  public:
    void 	SetXHalfLength1 (G4double val); 
    void 	SetXHalfLength2 (G4double val); 
    void 	SetYHalfLength1 (G4double val);
    void 	SetYHalfLength2 (G4double val); 
    void 	SetZHalfLength (G4double val);

  private:
    TrdComponentBuilderMessenger* fMessenger;
    
    G4Trd* fSolid;
    G4LogicalVolume* fLogic;
    VMaterialFactory* fMatFactory;
    
    G4double fDx1,fDx2,fDy1,fDy2,fDz;  
           
};


#endif


