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

#ifndef NuSDSiPMROUnitBuilder_h
#define NuSDSiPMROUnitBuilder_h 1

#include "NuSDVROUnitCompBuilder.hh"
#include "NuSDAxisType.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

class NuSDSiPMROUnitBuilderMessenger;
class BoxComponentBuilder;
class G4LogicalVolume;
class OpticalSurface;
class MaterialPropertiesHelper;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDSiPMROUnitBuilder : public NuSDVROUnitCompBuilder{

  public:
    NuSDSiPMROUnitBuilder(const G4String& name, const G4String& matName, NuSDAxisType axisType); 
    virtual ~NuSDSiPMROUnitBuilder();
    
    virtual void CreateMaterial() override;
    virtual void Construct()  override;
    virtual void CreateSubComponentBuilders() override;
    virtual void PlaceSubComponents() override;
    
    private:
      void SetPrivateSurfaceAndMaterialProperties();
     
  private:
    void SetComponentsDimensions(G4ThreeVector& unitVec);
    void SetComponentsPositions(G4ThreeVector& psBinderPos, G4ThreeVector& psPos);
    void SetComponentsRotations(G4RotationMatrix* psBinderRot, G4RotationMatrix* psRot);
  
  public:
    void SetReflectorSurfaceFlag(G4bool bl); 
    void SetPhotoSensorBinderFlag(G4bool bl);
  
  //Getters     
  public:    
   // BoxComponentBuilder* GetPhotoSensorBinder() const { return fPhotoSensorBinder; }
   // BoxComponentBuilder* GetPhotoSensor()       const{ return fPhotoSensor; }
        
  private:
    NuSDSiPMROUnitBuilderMessenger *fMessenger;
    MaterialPropertiesHelper* fReflectorMatProp;
    OpticalSurface* fReflectorSurface;
   
    
    BoxComponentBuilder*  fPSBinderBuilder;
    BoxComponentBuilder*  fPSBuilder;
    
    G4bool bReflector;
    G4bool bPSBinder;
                   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
