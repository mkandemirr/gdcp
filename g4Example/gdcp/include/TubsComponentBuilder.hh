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

#ifndef TubsComponentBuilder_h
#define TubsComponentBuilder_h 1

#include "VComponentBuilder.hh"

class TubsComponentBuilderMessenger;
class G4Tubs;
class VMaterialFactory;
class G4LogicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TubsComponentBuilder : public VComponentBuilder{

  public:
    TubsComponentBuilder( const G4String& name, 
                          const G4String& matName, 
                          VMaterialFactory* matFactory,
                          G4double pRMin=0., 
                          G4double pRMax=0., 
                          G4double pDz=0., 
                          G4double pSPhi=0., 
                          G4double pDPhi=0.,
                          G4bool pSensitive=false
                        );
    virtual ~TubsComponentBuilder();
    
    virtual void CreateMaterial() override;
    virtual void Construct()  override;
      
  //Gettters 
  public:    
    G4double GetInnerRadius() const { return fInnerRadius;} 
    G4double GetOuterRadius() const { return fOuterRadius;}         
    G4double GetZHalfLength() const { return fZHalfLength; }
    G4double GetStartPhiAngle() const { return fStartPhiAngle; } 
    G4double GetDeltaPhiAngle() const { return fDeltaPhiAngle; }    
   
  //Setters  
  public:
    void SetInnerRadius(G4double pRmin); 
    void SetOuterRadius(G4double pRMax);         
    void SetZHalfLength(G4double pDz);
    void SetStartPhiAngle(G4double pSphi); 
    void SetDeltaPhiAngle(G4double pDPhi); 
    
  private:
    TubsComponentBuilderMessenger* fMessenger;
    
    G4Tubs* fSolid;
    G4LogicalVolume* fLogic;
    VMaterialFactory* fMatFactory;
                  
    G4double  fInnerRadius;
    G4double  fOuterRadius;
    G4double  fZHalfLength;
    G4double  fStartPhiAngle;
    G4double  fDeltaPhiAngle;
                 
};

#endif

