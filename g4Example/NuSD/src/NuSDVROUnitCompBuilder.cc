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
//
//
/// \file optical/LXe/src/NuSDVROUnitCompBuilder.cc
/// \brief Implementation of the NuSDVROUnitCompBuilder class
//
//
#include "NuSDVROUnitCompBuilder.hh"
#include "GeometryManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDVROUnitCompBuilder::NuSDVROUnitCompBuilder(const G4String& name, const G4String& matName, NuSDAxisType placedAxis) : 
VMultiComponentBuilder(name, matName),
pPlacedAxis{placedAxis},
pGeometryManager{GeometryManager::GetInstance()}            
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDVROUnitCompBuilder::~NuSDVROUnitCompBuilder()
{  
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


