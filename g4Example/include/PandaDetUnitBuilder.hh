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

#ifndef PandaDetUnitBuilder_h
#define PandaDetUnitBuilder_h 1

#include "NuSDVDetUnitCompBuilder.hh"

class BoxComponentBuilder;
class NuSDGammaScntCompBuilder;
class MaterialPropertiesHelper;
class OpticalSurface;

class PandaDetUnitBuilder : public NuSDVDetUnitCompBuilder{

  public:
    PandaDetUnitBuilder(const G4String& name, const G4String& matName);
    virtual ~PandaDetUnitBuilder();
    
    virtual void CreateMaterial() override;
    virtual void CreateSubComponentBuilders() override;
    virtual void Construct()  override;
    virtual void PlaceSubComponents() override;
    
    virtual const VComponentBuilder* SetSensorAttachedComponent() override; 
    
  private:
    void SetPrivateSurfaceAndMaterialProperties();
  
    
  
  public:
   NuSDGammaScntCompBuilder* GetGammaScnt() { return fGammaScnt;}
   
  private:                  
    MaterialPropertiesHelper* fReflectorMatProp;
    OpticalSurface*    fReflectorSurface;
    
    NuSDGammaScntCompBuilder* fGammaScnt;
    BoxComponentBuilder*      fOptBarrier;
    BoxComponentBuilder*      fReflector;
    BoxComponentBuilder*      fGd;
    
    G4double fOptBarrierThick;  
    G4double fReflectorThick;
    G4double fGdThick;
      
    //G4bool   fIsPSOn;  
    //UI--- Finish---------------
      
};


#endif


