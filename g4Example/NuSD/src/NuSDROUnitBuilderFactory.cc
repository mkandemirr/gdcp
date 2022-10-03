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

#include "NuSDROUnitBuilderFactory.hh"
#include "NuSDSiPMROUnitBuilder.hh"
#include "NuSDPmtROUnitBuilder.hh"
#include "GeometryManager.hh"
#include "NuSDSiPMROUnitPlacer.hh"
#include "NuSDPmtROUnitPlacer.hh"
#include "NuSDDetectorBuilder.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDROUnitBuilderFactory::NuSDROUnitBuilderFactory()           
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDROUnitBuilderFactory::~NuSDROUnitBuilderFactory()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDVROUnitCompBuilder* NuSDROUnitBuilderFactory::Create(NuSDDetectorBuilder* detBuilder, NuSDPhotoSensorType psType, NuSDAxisType axis)
{
  //NuSDDetectorBuilder* detBuilder = static_cast<NuSDDetectorBuilder*>(GeometryManager::GetInstance()->GetDetBuilder()); 
  
  if(psType==NuSDPhotoSensorType::ePMT)
  {
    detBuilder->SetROUnitPlacer(new NuSDPmtROUnitPlacer());
    if(axis == NuSDAxisType::eXAxis)
      return new NuSDPmtROUnitBuilder("PmtROUnitX","Air", NuSDAxisType::eXAxis);
    else if(axis == NuSDAxisType::eYAxis)
      return new NuSDPmtROUnitBuilder("PmtROUnitY","Air", NuSDAxisType::eYAxis);
    else if(axis == NuSDAxisType::eZAxis)
      return new NuSDPmtROUnitBuilder("PmtROUnitZ","Air", NuSDAxisType::eZAxis);
  }else if(psType==NuSDPhotoSensorType::eSiPM)
  {
    detBuilder->SetROUnitPlacer(new NuSDSiPMROUnitPlacer());
    if(axis == NuSDAxisType::eXAxis)
      return new NuSDSiPMROUnitBuilder("SiPMROUnitX","Air", NuSDAxisType::eXAxis);
    else if(axis == NuSDAxisType::eYAxis)
      return new NuSDSiPMROUnitBuilder("SiPMROUnitY", "Air", NuSDAxisType::eYAxis);
    else if(axis == NuSDAxisType::eZAxis)
      return new NuSDSiPMROUnitBuilder("SiPMROUnitZ", "Air", NuSDAxisType::eZAxis);
    
  }
  
  return nullptr; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


