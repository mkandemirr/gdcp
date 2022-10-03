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

#ifndef NuSDGammaScntCompBuilder_h
#define NuSDGammaScntCompBuilder_h 1

#include "BoxComponentBuilder.hh"
#include "G4Cache.hh"

class G4Box;
class G4LogicalVolume;
class NuSDGammaScntSD;
//class NuSDGammaScntCompBuilderMessenger;

class NuSDGammaScntCompBuilder : public BoxComponentBuilder{

  public:
    NuSDGammaScntCompBuilder(const G4String& name, 
                            const G4String& matName, 
                            G4double dx=0.,G4double dy=0.,G4double dz=0.,
                            G4bool sensitive=true
                            );                    
    virtual ~NuSDGammaScntCompBuilder();
    
    virtual void ConstructSDAndField();
       
 
  private:
    //NuSDGammaScntCompBuilderMessenger* fMessenger;
    G4Cache<NuSDGammaScntSD*>  fGammaScntSD;
              
};


#endif


