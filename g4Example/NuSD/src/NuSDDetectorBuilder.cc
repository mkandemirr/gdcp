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


#include "NuSDDetectorBuilder.hh"
#include "NuSDDetectorBuilderMessenger.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "NuSDVDetUnitCompBuilder.hh"
#include "NuSDVROUnitCompBuilder.hh"
#include "NuSDAxisType.hh"

#include "NuSDVROUnitPlacer.hh"
#include "NuSDVDetUnitPlacer.hh"

#include "NuSDROUnitBuilderFactory.hh"

#include "NuSDGrooveCompBuilderStore.hh"
#include "NuSDSimManager.hh"
#include "G4UImanager.hh"
#include "NuSDVGrooveCompBuilder.hh"
#include "SmartComponent.hh"
#include "NuSDMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDDetectorBuilder::NuSDDetectorBuilder(const G4String& name, 
                                         const G4String& matName, 
                                         NuSDVDetUnitCompBuilder* detUnitBuilder, 
                                         NuSDVDetUnitPlacer* placer
                                        ): VMultiComponentBuilder(name, matName),                                       
fMessenger{nullptr},                  
fDetUnitBuilder{detUnitBuilder},
ePhotoSensorType{NuSDPhotoSensorType::eNotDefined},
fDetUnitPlacer{placer},
fROUnitPlacer{nullptr},
bROUnitX{true},
bROUnitY{false},
bROUnitZ{true},
fNumberOfSegmentAlongX{1},
fNumberOfSegmentAlongY{1},
fNumberOfSegmentAlongZ{1},
fEndSideDetUnitVecX(),
fEndSideDetUnitVecY(),
fEndSideDetUnitVecZ(),
fROUnitBuilderVecX(),
fROUnitBuilderVecY(),
fROUnitBuilderVecZ()
{
   
  fMessenger = new NuSDDetectorBuilderMessenger(this);
  G4UImanager* uImanager = G4UImanager::GetUIpointer();
  uImanager->ApplyCommand("/control/execute macros/detectorBuilder.mac"); 
  
  pProduct = new SmartComponent(pName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDDetectorBuilder::~NuSDDetectorBuilder()
{
  if(fMessenger)  delete fMessenger; 
  if(pProduct)    delete pProduct; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::CreateSubComponentBuilders()
{
  //fDetUnitBuilder->CreateSubComponentBuilders();
  
  if(ePhotoSensorType==NuSDPhotoSensorType::ePMT)
  {
    CreatePMTBuilders();
    
  }else if(ePhotoSensorType==NuSDPhotoSensorType::eSiPM)
  {
    CreateSiPMBuilders();
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::CreatePMTBuilders()
{
  if(bROUnitX)
    fROUnitBuilderVecX.push_back(NuSDROUnitBuilderFactory::Create(this, ePhotoSensorType, NuSDAxisType::eXAxis)); 
  if(bROUnitY)
    fROUnitBuilderVecY.push_back(NuSDROUnitBuilderFactory::Create(this, ePhotoSensorType, NuSDAxisType::eYAxis)); 
  if(bROUnitZ)
    fROUnitBuilderVecZ.push_back(NuSDROUnitBuilderFactory::Create(this, ePhotoSensorType, NuSDAxisType::eZAxis));  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::CreateSiPMBuilders()
{ 
  NuSDGrooveCompBuilderStore* store = NuSDGrooveCompBuilderStore::GetInstance();

  for(std::size_t j=0;j<store->size();++j)
  {
    if(bROUnitX && store->at(j)->GetPlacedAxis()==NuSDAxisType::eXAxis)
      fROUnitBuilderVecX.push_back(NuSDROUnitBuilderFactory::Create(this, ePhotoSensorType, NuSDAxisType::eXAxis)); 
    
    if(bROUnitY && store->at(j)->GetPlacedAxis()==NuSDAxisType::eYAxis)
      fROUnitBuilderVecY.push_back(NuSDROUnitBuilderFactory::Create(this, ePhotoSensorType, NuSDAxisType::eYAxis)); 
    
    if(bROUnitZ && store->at(j)->GetPlacedAxis()==NuSDAxisType::eZAxis)
      fROUnitBuilderVecZ.push_back(NuSDROUnitBuilderFactory::Create(this, ePhotoSensorType, NuSDAxisType::eZAxis));
      
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::CreateMaterial()
{
  pMaterial = NuSDMaterialFactory::GetInstance()->FindOrCreateMaterial(pMatName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::Construct()
{
  CreateMaterial();
  //Construct detector unit
  fDetUnitBuilder->Construct();  
    
  //Construct readoutUnits  
  if(bROUnitX)
  {
    for(std::size_t i=0;i<fROUnitBuilderVecX.size();++i)
      fROUnitBuilderVecX.at(i)->Construct();
  }
  
  if(bROUnitY)
  {
    for(std::size_t i=0;i<fROUnitBuilderVecY.size();++i)
      fROUnitBuilderVecY.at(i)->Construct();
  }
  
  if(bROUnitZ)
  {
    for(std::size_t i=0;i<fROUnitBuilderVecZ.size();++i)
      fROUnitBuilderVecZ.at(i)->Construct();
  }
  
  //Construct full detector. Before construction, 
  //adjust the dimensions.  
  G4Box* detUnitBox = (G4Box*)fDetUnitBuilder->GetProduct()->GetSolid();
  
  G4double detUnitSizeX = 2*detUnitBox->GetXHalfLength();
  G4double detUnitSizeY = 2*detUnitBox->GetYHalfLength();
  G4double detUnitSizeZ = 2*detUnitBox->GetZHalfLength();
  
  G4double readoutUnitSizeX{0.};
  G4double readoutUnitSizeY{0.};
  G4double readoutUnitSizeZ{0.};
  
  if(bROUnitX)
  {
    G4Box* box = (G4Box*)fROUnitBuilderVecX.at(0)->GetProduct()->GetSolid();
    readoutUnitSizeX = 2*box->GetXHalfLength();  
  }
  
  if(bROUnitY)
  {
    G4Box* box = (G4Box*)fROUnitBuilderVecY.at(0)->GetProduct()->GetSolid();  
    readoutUnitSizeY = 2*box->GetYHalfLength(); 
  }
  
  if(bROUnitZ)
  {
    G4Box* box = (G4Box*)fROUnitBuilderVecZ.at(0)->GetProduct()->GetSolid();
    readoutUnitSizeZ = 2*box->GetZHalfLength();  
  }
   
  G4double gap{3.*cm};//gap between mainVol and world.
  
  G4double sizeX  = fNumberOfSegmentAlongX*detUnitSizeX + 2*readoutUnitSizeX + gap;
  G4double sizeY  = fNumberOfSegmentAlongY*detUnitSizeY + 2*readoutUnitSizeY + gap;
  G4double sizeZ  = fNumberOfSegmentAlongZ*detUnitSizeZ + 2*readoutUnitSizeZ + gap; 
  
  G4Box*           solid  = new G4Box("DetectorSolid", 0.5*sizeX, 0.5*sizeY, 0.5*sizeZ);
  G4LogicalVolume* logic  = new G4LogicalVolume(solid, pMaterial, "DetectorLogic", 0, 0, 0);
 
  pProduct->SetLogicalVolume(logic);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlaceSubComponents()
{
  if(!pProduct->GetLogicalVolume())
  {
    G4Exception("NuSDDetectorBuilder.cc", "Err0", FatalException, 
                "logical volume of the smart product should be set."
               );
  } 
  
  //Place detector units  
  fDetUnitPlacer->Place(fDetUnitBuilder->GetProduct());
  
  //Place optical readout units
  if(bROUnitX) PlaceROUnitsXDirection();
  if(bROUnitY) PlaceROUnitsYDirection();
  if(bROUnitZ) PlaceROUnitsZDirection();
  
  fROUnitBuilderVecX.clear();
  fROUnitBuilderVecY.clear();
  fROUnitBuilderVecZ.clear();
  
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlaceROUnitsXDirection()
{
  if(ePhotoSensorType==NuSDPhotoSensorType::ePMT)
    PlacePMTsXDirection();
  else if(ePhotoSensorType==NuSDPhotoSensorType::eSiPM)
    PlaceSiPMsXDirection();       
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlacePMTsXDirection()
{
  for(std::size_t i=0; i<fEndSideDetUnitVecX.size(); ++i)
    fROUnitPlacer->Place(fEndSideDetUnitVecX.at(i), fROUnitBuilderVecX.at(0));     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlaceSiPMsXDirection()
{
  for(std::size_t i=0; i<fEndSideDetUnitVecX.size(); ++i)
  {
    
    NuSDGrooveCompBuilderStore* store = NuSDGrooveCompBuilderStore::GetInstance();

    int k=0;
    for(std::size_t j=0;j<store->size();++j)
    {
      if(store->at(j)->GetPlacedAxis()==NuSDAxisType::eXAxis)
      {
        fROUnitPlacer->Place(fEndSideDetUnitVecX.at(i), store->at(j), fROUnitBuilderVecX.at(k));
        k++;
      }
    }
         
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlaceROUnitsYDirection()
{
  if(ePhotoSensorType==NuSDPhotoSensorType::ePMT)
    PlacePMTsYDirection();
  else if(ePhotoSensorType==NuSDPhotoSensorType::eSiPM)
    PlaceSiPMsYDirection();       
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlacePMTsYDirection()
{
  for(std::size_t i=0; i<fEndSideDetUnitVecY.size(); ++i)
    fROUnitPlacer->Place(fEndSideDetUnitVecY.at(i), fROUnitBuilderVecY.at(0));     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlaceSiPMsYDirection()
{
  for(std::size_t i=0; i<fEndSideDetUnitVecY.size(); ++i)
  {
    NuSDGrooveCompBuilderStore* store = NuSDGrooveCompBuilderStore::GetInstance();
    
    int k=0;
    for(std::size_t j=0;j<store->size();++j)
    {
      if(store->at(j)->GetPlacedAxis()==NuSDAxisType::eYAxis)
      {  
        fROUnitPlacer->Place(fEndSideDetUnitVecY.at(i), store->at(j), fROUnitBuilderVecY.at(k) );
        k++;
      }
        
    }
         
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlaceROUnitsZDirection()
{
  if(ePhotoSensorType==NuSDPhotoSensorType::ePMT)
    PlacePMTsZDirection();
  else if(ePhotoSensorType==NuSDPhotoSensorType::eSiPM)
    PlaceSiPMsZDirection();       
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlacePMTsZDirection()
{
  for(std::size_t i=0; i<fEndSideDetUnitVecZ.size(); ++i)
    fROUnitPlacer->Place(fEndSideDetUnitVecZ.at(i), fROUnitBuilderVecZ.at(0));     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::PlaceSiPMsZDirection()
{
  for(std::size_t i=0; i<fEndSideDetUnitVecZ.size(); ++i)
  {
    NuSDGrooveCompBuilderStore* store = NuSDGrooveCompBuilderStore::GetInstance();
    
    int k=0;
    for(std::size_t j=0;j<store->size();++j)
    {
      if(store->at(j)->GetPlacedAxis()==NuSDAxisType::eZAxis)
      {
        fROUnitPlacer->Place(fEndSideDetUnitVecZ.at(i), store->at(j), fROUnitBuilderVecZ.at(k));
        k++;
      }
        
    }
         
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
void NuSDDetectorBuilder::SetNumberOfSegmentAlongX(G4int x)
{
  fNumberOfSegmentAlongX = x;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::SetNumberOfSegmentAlongY(G4int y)
{
  fNumberOfSegmentAlongY = y;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::SetNumberOfSegmentAlongZ(G4int z)
{
  fNumberOfSegmentAlongZ = z;
}



void NuSDDetectorBuilder::SetPhotoSensorType(NuSDPhotoSensorType type)
{
  ePhotoSensorType = type;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::SetROUnitXFlag(G4bool bl) 
{ 
  bROUnitX = bl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::SetROUnitYFlag(G4bool bl) 
{ 
  bROUnitY = bl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::SetROUnitZFlag(G4bool bl) 
{ 
  bROUnitZ = bl;
}

void NuSDDetectorBuilder::SetROUnitXBothEndFlag(G4bool bl)
{
  bROUnitXBothEnd = bl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::SetROUnitYBothEndFlag(G4bool bl)
{
  bROUnitYBothEnd = bl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDDetectorBuilder::SetROUnitZBothEndFlag(G4bool bl)
{
  bROUnitZBothEnd = bl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
