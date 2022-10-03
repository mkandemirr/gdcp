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

#ifndef NuSDPmtROUnitBuilder_h
#define NuSDPmtROUnitBuilder_h 1

#include "NuSDVROUnitCompBuilder.hh"
#include "NuSDAxisType.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class NuSDPmtROUnitBuilderMessenger;
class TrdComponentBuilder;
class BoxComponentBuilder;
class TubsComponentBuilder;
class NuSDVPhotoSensor;
class OpticalSurface;
class MaterialPropertiesHelper;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDPmtROUnitBuilder : public NuSDVROUnitCompBuilder{

  public:
    NuSDPmtROUnitBuilder(const G4String& name, const G4String& matName, NuSDAxisType axisType); 
    virtual ~NuSDPmtROUnitBuilder();
    
    virtual void CreateMaterial() override;
    virtual void Construct()  override;
    virtual void CreateSubComponentBuilders() override;
    virtual void PlaceSubComponents() override;
    
  private:
    void SetPrivateSurfaceAndMaterialProperties();
     
  private: 
    void SetComponentsDimensions(G4ThreeVector& unitVec);
    
    void SetComponentsPositions(G4ThreeVector& lgBinderPos, 
                               G4ThreeVector& lgPos, 
                               G4ThreeVector& psBinderPos, 
                               G4ThreeVector& psPos
                               );
    
    void SetComponentsRotations(G4RotationMatrix* lgBinderRot,
                               G4RotationMatrix* lgRot, 
                               G4RotationMatrix* psBinderRot, 
                               G4RotationMatrix* psRot
                               );    
  public:
    void SetReflectorSurfaceFlag(G4bool bl); 
    void SetLightGuideFlag(G4bool bl);
    void SetLightGuideBinderFlag(G4bool bl);
    void SetPhotoSensorBinderFlag(G4bool bl);
    
  private:
    NuSDPmtROUnitBuilderMessenger * fMessenger;
    MaterialPropertiesHelper* fReflectorMatProp;
    OpticalSurface* fReflectorSurface;
    
    BoxComponentBuilder*   fLgBinderBuilder;
    TrdComponentBuilder*   fLgBuilder;
    TubsComponentBuilder*  fPSBinderBuilder;
    TubsComponentBuilder*  fPSBuilder;
    
    G4bool bReflector;
    G4bool bLg;
    G4bool bLgBinder;
    G4bool bPSBinder;
                
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
