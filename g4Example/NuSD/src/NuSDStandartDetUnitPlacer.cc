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

#include "NuSDStandartDetUnitPlacer.hh"
#include "NuSDDetectorBuilder.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "GeometryManager.hh"
#include "SmartComponent.hh"
#include "SmartComponent.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDStandartDetUnitPlacer::NuSDStandartDetUnitPlacer() : 
NuSDVDetUnitPlacer()
            
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDStandartDetUnitPlacer::~NuSDStandartDetUnitPlacer()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDStandartDetUnitPlacer::Place(SmartComponent* detUnit)
{

  NuSDDetectorBuilder* detBuilder = static_cast<NuSDDetectorBuilder*>(pGeometryManager->GetDetBuilder());

  G4int numberOfSegmentAlongX = detBuilder->GetNumberOfSegmentAlongX();
  G4int numberOfSegmentAlongY = detBuilder->GetNumberOfSegmentAlongY();
  G4int numberOfSegmentAlongZ = detBuilder->GetNumberOfSegmentAlongZ();
  
  G4Box* box = (G4Box*)detUnit->GetLogicalVolume()->GetSolid();
  
  G4double unitSizeX = 2*box->GetXHalfLength();
  G4double unitSizeY = 2*box->GetYHalfLength();
  G4double unitSizeZ = 2*box->GetZHalfLength();
  
  G4double x{}, y{}, z{};  //unit center position coordinates with respect to its mother.
  
  //----------Place Units in MainVol--------------------    	 

  for(G4int i=0; i<numberOfSegmentAlongY; ++i)
  { 

    y =  -unitSizeY*(numberOfSegmentAlongY-1)*0.5 + i*unitSizeY;

    //xz layer       
    for(G4int j =0; j<numberOfSegmentAlongX; ++j)
    {

      x = -unitSizeX*(numberOfSegmentAlongX-1)*0.5 + j*unitSizeX;

      for(G4int k =0; k<numberOfSegmentAlongZ; ++k)
      {      

        z = -unitSizeZ*(numberOfSegmentAlongZ-1)*0.5 + k*unitSizeZ; 

        
        G4VPhysicalVolume* physUnit = new G4PVPlacement(0, 
                                          G4ThreeVector(x,y,z), 
                                          detUnit->GetLogicalVolume(), 
                                          "UnitPV", 
                                          detBuilder->GetProduct()->GetLogicalVolume(), 
                                          false, 
                                          detUnit->GetPlacementList().size(), //copyNo 
                                          true
                                          );  
                                            
        //detBuilder->GetDetUnitVec().push_back(physUnit);
        detUnit->GetPlacementList().push_back(physUnit);
      
        if(i==0)
          detBuilder->GetEndSideDetUnitVecY().push_back(physUnit);
           
        if(j==0)
          detBuilder->GetEndSideDetUnitVecX().push_back(physUnit);
          
        if(k==0)
          detBuilder->GetEndSideDetUnitVecZ().push_back(physUnit);
        
      } //k loop


    }//j loop

  }//i loop

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


