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


#ifndef NuSDVDetUnitCompBuilder_h
#define NuSDVDetUnitCompBuilder_h 1

#include "VMultiComponentBuilder.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NuSDVDetUnitCompBuilder : public VMultiComponentBuilder {

  public:
    NuSDVDetUnitCompBuilder(const G4String& name, const G4String& matName); 
    virtual ~NuSDVDetUnitCompBuilder();
  
  public:
    virtual const VComponentBuilder* SetSensorAttachedComponent() { return nullptr; } 
    
    const VComponentBuilder* GetSensorAttachedComponent() { return SetSensorAttachedComponent(); }
            
};

#endif

