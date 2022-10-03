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

#include "NuSDSiPMROUnitPlacer.hh"
#include "NuSDDetectorBuilder.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "NuSDVROUnitCompBuilder.hh"
#include "GeometryManager.hh"
#include "NuSDVGrooveCompBuilder.hh"
#include "G4LogicalVolume.hh"
#include "SmartComponent.hh"
#include "SmartComponent.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSiPMROUnitPlacer::NuSDSiPMROUnitPlacer() : 
NuSDVROUnitPlacer()
            
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSiPMROUnitPlacer::~NuSDSiPMROUnitPlacer()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void NuSDSiPMROUnitPlacer::Place(const G4VPhysicalVolume* detectorUnit, 
                               const NuSDVGrooveCompBuilder* grooveComp, 
                               NuSDVROUnitCompBuilder* readoutUnitBuilder 
                              )
{
  SmartComponent* readoutUnit = readoutUnitBuilder->GetProduct();
  //This readoutUnit will be mounted to this detectorUnit. 
  NuSDDetectorBuilder* detBuilder = static_cast<NuSDDetectorBuilder*>(pGeometryManager->GetDetBuilder());
 
  //Before placement,obtain the readoutUnit position vector
  G4ThreeVector readoutUnitPos = GetROUnitPos(detectorUnit, grooveComp, readoutUnitBuilder); 
 
  //the below code is the same for both PMT and SiPM
  
  G4VPhysicalVolume* readoutUnitPV{nullptr};
  
  //place readoutUnit in detBuilder                            
  readoutUnitPV  = new G4PVPlacement(0, 
                        readoutUnitPos, 
                        readoutUnit->GetLogicalVolume(), 
                        "ROUnitPV", 
                        detBuilder->GetProduct()->GetLogicalVolume(), 
                        false, 
                        readoutUnit->GetPlacementList().size(), //copyNo 
                        true
                        );                            
                             
  readoutUnit->GetPlacementList().push_back(readoutUnitPV);   
 
  //Check readoutUnits will be placed both end!!
  
  if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eXAxis)
  {
    if(!detBuilder->IsROUnitXAddedBothEnd())
      return;
  }else if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eYAxis)
  {
    if(!detBuilder->IsROUnitYAddedBothEnd())
      return;
    
  }else
  {
    if(!detBuilder->IsROUnitZAddedBothEnd())
      return;  
  } 
  
  
  if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eXAxis)
    readoutUnitPos.setX(-readoutUnitPos.getX());
  else if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eYAxis)
    readoutUnitPos.setY(-readoutUnitPos.getY()); 
  else if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eZAxis)
    readoutUnitPos.setZ(-readoutUnitPos.getZ());  
  
  //rotate and place..
  G4RotationMatrix* readoutUnitRot = new G4RotationMatrix;
  
  if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eXAxis)
    readoutUnitRot->rotateZ(180*deg);
  else if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eYAxis)
    readoutUnitRot->rotateZ(180*deg); 
  else if(readoutUnitBuilder->GetPlacedAxis() == NuSDAxisType::eZAxis)
    readoutUnitRot->rotateX(180*deg); 

  //Place opposite end!  
  readoutUnitPV  = new  G4PVPlacement(readoutUnitRot, 
                        readoutUnitPos, 
                        readoutUnit->GetLogicalVolume(), 
                        "ROUnitPV", 
                        detBuilder->GetProduct()->GetLogicalVolume(), 
                        false, 
                        readoutUnit->GetPlacementList().size(), //copyNo 
                        true
                        );   
  
  readoutUnit->GetPlacementList().push_back(readoutUnitPV);   

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreeVector NuSDSiPMROUnitPlacer::GetROUnitPos(const G4VPhysicalVolume* detectorUnit, 
                                              const NuSDVGrooveCompBuilder* grooveComp, 
                                              const NuSDVROUnitCompBuilder* readoutUnitBuilder
                                              )
{
  SmartComponent* readoutUnit = readoutUnitBuilder->GetConstProduct();
   //Get readout attached detector units dimensions
  G4Box* detUnitBox = (G4Box*)detectorUnit->GetLogicalVolume()->GetSolid();
  
  G4double unitSizeX = 2*detUnitBox->GetXHalfLength();
  G4double unitSizeY = 2*detUnitBox->GetYHalfLength();
  G4double unitSizeZ = 2*detUnitBox->GetZHalfLength();
  
  //Get readoutUnit dimensions
  G4Box* readoutUnitSolid = (G4Box*)readoutUnit->GetLogicalVolume()->GetSolid();
  
  G4double readoutUnitSizeX = 2*readoutUnitSolid->GetXHalfLength();
  G4double readoutUnitSizeY = 2*readoutUnitSolid->GetYHalfLength();
  G4double readoutUnitSizeZ = 2*readoutUnitSolid->GetZHalfLength();
  
  //Get readoutUnit position
  G4ThreeVector detUnitPos = detectorUnit->GetTranslation();
  G4ThreeVector grooveCenterPosVec = detUnitPos + grooveComp->GetConstProduct()->
                                     GetPhysicalVolume()->GetTranslation(); //wrt detBuilder
  G4ThreeVector readoutUnitPos;
  
  if(readoutUnitBuilder->GetPlacedAxis()==NuSDAxisType::eXAxis)
  {
                                                                               
    readoutUnitPos = G4ThreeVector(grooveCenterPosVec.getX()-unitSizeX*0.5-readoutUnitSizeX*0.5,
                                   grooveCenterPosVec.getY(),
                                   grooveCenterPosVec.getZ()
                                   );
                              
  }else if(readoutUnitBuilder->GetPlacedAxis()==NuSDAxisType::eYAxis)
  {
                                                                 
    readoutUnitPos = G4ThreeVector(grooveCenterPosVec.getX(),
                                   grooveCenterPosVec.getY()-unitSizeY*0.5-readoutUnitSizeY*0.5,
                                   grooveCenterPosVec.getZ()
                                   );
    
    
  
  }else if(readoutUnitBuilder->GetPlacedAxis()==NuSDAxisType::eZAxis)
  {
          
    readoutUnitPos = G4ThreeVector(grooveCenterPosVec.getX(),
                                   grooveCenterPosVec.getY(),
                                   grooveCenterPosVec.getZ()-unitSizeZ*0.5-readoutUnitSizeZ*0.5
                                  );
    
  }
  
  return readoutUnitPos;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


