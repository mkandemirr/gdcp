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

#ifndef SolidGrooveCompBuilder_H
#define SolidGrooveCompBuilder_H 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NuSDVGrooveCompBuilder.hh"

#include "NuSDAxisType.hh"
#include "G4ThreeVector.hh"

class BoxComponentBuilder;


class SolidGrooveCompBuilder : public NuSDVGrooveCompBuilder
{
  public:
    SolidGrooveCompBuilder(const G4String& name, const G4String& matName, NuSDAxisType placedAxis);
    virtual ~SolidGrooveCompBuilder();

    virtual void CreateMaterial() override;
    virtual void Construct() override;
    virtual void CreateSubComponentBuilders() override;
    virtual void PlaceSubComponents() override;
    
 private:
  void SetComponentsDimensions(G4ThreeVector& unitVec);
     
  private:
    BoxComponentBuilder* fCore;
    BoxComponentBuilder* fInnerClad;
    BoxComponentBuilder* fOuterClad;
    
    G4double fInnerCladThickness;
    G4double fOutherCladThickness; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
