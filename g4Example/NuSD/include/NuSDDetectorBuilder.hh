//***********************************************************************
//* Neutrino Segmented Detector (NuSD) Copyright 2022 Mustafa Kandemir  *
//*                                                                     *
//* This file is part of NuSD.                                          *
//*                                                                     *
//* NuSD is free software: you can redistribute it and/or modify        * 
//* it under the terms of the GNU General Public License as published   *
//* by the Free Software Foundation, either version 3 of the License,   *
//* or any later version.                                               *
//*                                                                     *
//* NuSD is distributed in the hope that it will be useful, but         *
//* WITHOUT ANY WARRANTY; without even the implied warranty of          *
//* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        * 
//* GNU General Public License for more details.                        *
//*                                                                     *
//* You should have received a copy of the GNU General Public License   *
//* along with NuSD. If not, see <https://www.gnu.org/licenses/>.       *
//*                                                                     *
//***********************************************************************


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NuSDDetectorBuilder_h
#define NuSDDetectorBuilder_h 1

//#include "NuSDVROUnitCompBuilder.hh"

#include "NuSDPhotoSensorType.hh"
#include "NuSDStandartDetUnitPlacer.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "VMultiComponentBuilder.hh"


class NuSDVDetUnitPlacer;
class NuSDVROUnitPlacer;
class NuSDDetectorBuilderMessenger;
class VComponentBuilder;
class NuSDVDetUnitCompBuilder;
class NuSDVROUnitCompBuilder;
class NuSDVGrooveCompBuilder;
class G4VPhysicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDDetectorBuilder: public VMultiComponentBuilder {

  public: 
    NuSDDetectorBuilder(const G4String& name, 
                        const G4String& matName, 
                        NuSDVDetUnitCompBuilder* unitBuilder, 
                        NuSDVDetUnitPlacer* placer = new NuSDStandartDetUnitPlacer()
                       );
    virtual ~NuSDDetectorBuilder();
    
    virtual void CreateMaterial() override;
    virtual void CreateSubComponentBuilders() override;
    virtual void Construct() override;
    virtual void PlaceSubComponents() override;
    
  private:
    void CreatePMTBuilders();
    void CreateSiPMBuilders();  
      
    void PlaceROUnitsXDirection();
    void PlaceROUnitsYDirection();
    void PlaceROUnitsZDirection();
    
    void PlacePMTsXDirection();
    void PlacePMTsYDirection();
    void PlacePMTsZDirection();
    
    void PlaceSiPMsXDirection();
    void PlaceSiPMsYDirection();
    void PlaceSiPMsZDirection();
       
  public:
    //Setters,UI commands
    void SetNumberOfSegmentAlongX(G4int x);
    void SetNumberOfSegmentAlongY(G4int y);
    void SetNumberOfSegmentAlongZ(G4int z);
    
    void SetPhotoSensorType(NuSDPhotoSensorType type);
    
    void SetROUnitXFlag(G4bool bl);
    void SetROUnitYFlag(G4bool bl);
    void SetROUnitZFlag(G4bool bl);
    
    void SetROUnitXBothEndFlag(G4bool);
    void SetROUnitYBothEndFlag(G4bool);
    void SetROUnitZBothEndFlag(G4bool);
    
    //---
    void SetROUnitPlacer(NuSDVROUnitPlacer* pl) {fROUnitPlacer = pl; }
    void SetDetUnitPlacer(NuSDVDetUnitPlacer* pl) {fDetUnitPlacer = pl; }
    
    //void SetDetUnit(NuSDVDetUnitCompBuilder* unit) { fDetUnitBuilder = unit;}
    
    //Getters
    G4bool IsROUnitXAddedBothEnd() const { return bROUnitXBothEnd; }
    G4bool IsROUnitYAddedBothEnd() const { return bROUnitYBothEnd; }
    G4bool IsROUnitZAddedBothEnd() const { return bROUnitZBothEnd; }
    
    G4int GetNumberOfSegmentAlongX() const { return fNumberOfSegmentAlongX;}
    G4int GetNumberOfSegmentAlongY() const { return fNumberOfSegmentAlongY;}
    G4int GetNumberOfSegmentAlongZ() const { return fNumberOfSegmentAlongZ;}
    
    NuSDVDetUnitCompBuilder* GetDetUnitBuilder() const { return fDetUnitBuilder; }
    
    //Containers  
    std::vector<G4VPhysicalVolume*>& GetEndSideDetUnitVecX()  { return fEndSideDetUnitVecX; }
    std::vector<G4VPhysicalVolume*>& GetEndSideDetUnitVecY()  { return fEndSideDetUnitVecY; }
    std::vector<G4VPhysicalVolume*>& GetEndSideDetUnitVecZ()  { return fEndSideDetUnitVecZ; }
    
  private: 
    NuSDDetectorBuilderMessenger* fMessenger;
    
    NuSDVDetUnitCompBuilder* fDetUnitBuilder; 
    
    NuSDPhotoSensorType ePhotoSensorType;
        
    NuSDVDetUnitPlacer* fDetUnitPlacer;
    NuSDVROUnitPlacer*  fROUnitPlacer;
     
    G4bool bROUnitX;
    G4bool bROUnitY;
    G4bool bROUnitZ;   
    
    G4bool bROUnitXBothEnd;
    G4bool bROUnitYBothEnd;
    G4bool bROUnitZBothEnd;
       
    G4int fNumberOfSegmentAlongX;
    G4int fNumberOfSegmentAlongY;
    G4int fNumberOfSegmentAlongZ; 
    
    std::vector<G4VPhysicalVolume*> fEndSideDetUnitVecX;
    std::vector<G4VPhysicalVolume*> fEndSideDetUnitVecY;
    std::vector<G4VPhysicalVolume*> fEndSideDetUnitVecZ;
    
    std::vector<NuSDVROUnitCompBuilder*> fROUnitBuilderVecX;
    std::vector<NuSDVROUnitCompBuilder*> fROUnitBuilderVecY;
    std::vector<NuSDVROUnitCompBuilder*> fROUnitBuilderVecZ;
                        
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


