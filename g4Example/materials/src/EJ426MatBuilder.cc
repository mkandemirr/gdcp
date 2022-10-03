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

#include "EJ426MatBuilder.hh"

#include "G4Material.hh"
#include "MaterialPropertiesHelper.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialBuilderStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ426MatBuilder::EJ426MatBuilder(const G4String& name, G4bool enableMatProp):
VMaterialBuilder(name,enableMatProp) 
{
  if(enableMatProp)
  {
    G4UImanager* uImanager = G4UImanager::GetUIpointer();
    uImanager->ApplyCommand("/control/execute macros/matPropTable/"+name+".mac");
    
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ426MatBuilder::~EJ426MatBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* EJ426MatBuilder::CreateMaterial()          
{ 
  G4double density,a;
  G4int ncomponents,Z,A;
  
  G4Element *el_F         = pNistManager->FindOrBuildElement("F"); //Flourine
  G4Element *el_Zn        = pNistManager->FindOrBuildElement("Zn");
  G4Element* el_S         = pNistManager->FindOrBuildElement("S");  
  G4Element* el_Si        = pNistManager->FindOrBuildElement("Si");
  
  //EnrichedLi  
  G4Isotope *Li6  = new G4Isotope("Li6", Z=3, A=6, a= 6.015122795*g/mole);
  G4Isotope *Li7  = new G4Isotope("Li7", Z=3, A=7, a= 7.01600455*g/mole);

  G4Element* enrichedLi_el  = new G4Element("EnrichedLithium", "Li", ncomponents=2);
  enrichedLi_el->AddIsotope(Li6, 95.*perCent);
  enrichedLi_el->AddIsotope(Li7, 5.*perCent);
  
  //Table 23. Material input data used for IAT-Validation model of CS layers.
  G4Material *scin_mat    = new G4Material(pName, density=2.42*g/cm3, ncomponents =8);
  scin_mat->AddElement(enrichedLi_el, 3.93*perCent); ////3.70(Li6) + 0.23(Li7)
  scin_mat->AddElement(el_F,  12.31*perCent);
  scin_mat->AddElement(el_Zn, 43.58*perCent);
  scin_mat->AddElement(el_S,  21.37*perCent);
  scin_mat->AddElement(el_Si, 7.69*perCent);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("C"),  6.57*perCent);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("H"),  0.17*perCent);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("O"),  4.38*perCent);
    
  //G4cout<<"Li6 atomDensity(1/cm3): "<<(2.42*0.0393/(6.02*0.95+7.02*0.05))*6.02e+23*0.95<<G4endl;
 
  /*
  //Table 24. Material Input Data used for LANL-NCCR model of CS layers. LANL(Los Alamos National Laboratory)
  G4Material *scin_mat = new G4Material("EJ-426", density=1.5386*g/cm3, ncomponents =7);
  scin_mat->AddElement(enrichedLi_el, 4.84*perCent); //4.60(Li6) + 0.24(Li7)
  scin_mat->AddElement(el_F,  15.16*perCent);
  scin_mat->AddElement(el_Zn, 42.82*perCent);
  scin_mat->AddElement(el_S,  20.93*perCent);
  scin_mat->AddElement(fNistManager->FindOrBuildElement("C"),  9.74*perCent);
  scin_mat->AddElement(fNistManager->FindOrBuildElement("H"),  1.31*perCent);
  scin_mat->AddElement(fNistManager->FindOrBuildElement("O"),  5.19*perCent);
  */  
   
  return scin_mat;  
}

