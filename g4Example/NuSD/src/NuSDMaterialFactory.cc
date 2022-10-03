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


#include "NuSDMaterialFactory.hh"

#include "EJ200MatBuilder.hh"
#include "EJ260MatBuilder.hh"
#include "EJ426MatBuilder.hh"
#include "EJ335MatBuilder.hh"
#include "CustomEJ254MatBuilder.hh"
#include "CustomEJ309MatBuilder.hh"
#include "AirMatBuilder.hh"
#include "PmmaMatBuilder.hh"
#include "PolystyreneMatBuilder.hh"
#include "CementMatBuilder.hh"
#include "GreaseMatBuilder.hh"
#include "GdCoatingMatBuilder.hh"
#include "FepMatBuilder.hh"
#include "AluminizedMylarMatBuilder.hh"
#include "FluorinatedAcrylicMatBuilder.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDMaterialFactory* NuSDMaterialFactory::fInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDMaterialFactory::NuSDMaterialFactory():
VMaterialFactory(),
fEJ200MatBuilder{nullptr},
fEJ260MatBuilder{nullptr},
fEJ426MatBuilder{nullptr},
fEJ335MatBuilder{nullptr},
fEJ254MatBuilder{nullptr},
fEJ309MatBuilder{nullptr},
fAirMatBuilder{nullptr},
fCementMatBuilder{nullptr},
fGreaseMatBuilder{nullptr},
fPolytreneMatBuilder{nullptr},
fPmmaMatBuilder{nullptr},
fFluorinatedAcrylicMatBuilder{nullptr},
fAluminizedMylarMatBuilder{nullptr},
fFepMatBuilder{nullptr},
fGdCoatingMatBuilder{nullptr}
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDMaterialFactory::~NuSDMaterialFactory()
{	
  //if(fEJ200MatBuilder) delete fEJ200MatBuilder;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* NuSDMaterialFactory::GetMaterial(const G4String& name)
{
  if(name=="EJ-200" && !fEJ200MatBuilder)
  {
    fEJ200MatBuilder = new EJ200MatBuilder(name,true);
    return fEJ200MatBuilder->GetProduct();
  }else if(name=="EJ-260" && !fEJ260MatBuilder)
  {
    fEJ260MatBuilder = new EJ260MatBuilder(name);
    return fEJ260MatBuilder->GetProduct();
  }else if(name=="EJ-426" && !fEJ426MatBuilder)
  {
    fEJ426MatBuilder = new EJ426MatBuilder(name,true);
    return fEJ426MatBuilder->GetProduct();
  }else if(name=="EJ-335" && !fEJ335MatBuilder)
  {
    fEJ335MatBuilder = new EJ335MatBuilder(name);
    return fEJ335MatBuilder->GetProduct();
  }else if(name=="CustomEJ-254" && !fEJ254MatBuilder)
  {
    fEJ254MatBuilder = new CustomEJ254MatBuilder(name);
    return fEJ254MatBuilder->GetProduct();
  }else if(name=="CustomEJ-309" && !fEJ309MatBuilder)
  {
    fEJ309MatBuilder = new CustomEJ309MatBuilder(name);
    return fEJ309MatBuilder->GetProduct();
  }else if(name=="Air" && !fAirMatBuilder)
  {
    fAirMatBuilder = new AirMatBuilder(name,true);
    return fAirMatBuilder->GetProduct(); 
  }else if(name=="Polystyrene" && !fPolytreneMatBuilder)
  {
    fPolytreneMatBuilder = new PolystyreneMatBuilder(name,true);
    return fPolytreneMatBuilder->GetProduct();  
  }else if(name=="Pmma" && !fPmmaMatBuilder)
  {
    fPmmaMatBuilder = new PmmaMatBuilder(name,true);
    return fPmmaMatBuilder->GetProduct();  
  }else if(name=="GdCoating" && !fGdCoatingMatBuilder)
  {
    fGdCoatingMatBuilder = new GdCoatingMatBuilder(name,false); 
    return fGdCoatingMatBuilder->GetProduct();
  }else if(name=="Cement" && !fCementMatBuilder)
  {
    fCementMatBuilder = new CementMatBuilder(name);
    return fCementMatBuilder->GetProduct();
  }else if(name =="Grease" && !fGreaseMatBuilder)
  {
    fGreaseMatBuilder = new GreaseMatBuilder(name);
    return fGreaseMatBuilder->GetProduct();
  }else if(name =="Fep" && !fFepMatBuilder)
  {
    fFepMatBuilder = new FepMatBuilder(name,true);
    return fFepMatBuilder->GetProduct();
  }else if(name =="AluminizedMylar" && !fAluminizedMylarMatBuilder)
  {
    fAluminizedMylarMatBuilder = new AluminizedMylarMatBuilder(name,true);
    return fAluminizedMylarMatBuilder->GetProduct();
  }else if(name =="FluorinatedAcrylic" && !fFluorinatedAcrylicMatBuilder)
  {
    fFluorinatedAcrylicMatBuilder = new FluorinatedAcrylicMatBuilder(name,true);
    return fFluorinatedAcrylicMatBuilder->GetProduct();
  }else
  {
    return nullptr;
  }
  
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDMaterialFactory* NuSDMaterialFactory::GetInstance()
{
  if (fInstance == 0)
    {
      fInstance = new NuSDMaterialFactory();
    }
  return fInstance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


