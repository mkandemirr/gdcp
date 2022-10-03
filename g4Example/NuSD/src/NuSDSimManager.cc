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

#include "NuSDSimManager.hh"
#include "NuSDSimManagerMessenger.hh"

#include "G4RunManager.hh"
#include "G4StateManager.hh"
#include "G4RunManager.hh"
#include "NuSDDetConstruction.hh"
#include "NuSDDetectorBuilder.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSimManager* NuSDSimManager::fInstance = 0;

NuSDSimManager::NuSDSimManager():
fMessenger{nullptr},
fIsOpticalPhysicsOn{true}
{
  fMessenger = new NuSDSimManagerMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSimManager::~NuSDSimManager()
{
  delete fMessenger;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDSimManager* NuSDSimManager::GetInstance()
{
  if (fInstance == 0)
    {
      fInstance = new NuSDSimManager();
    }
  return fInstance;
}

/*
NuSDDetectorBuilder* NuSDSimManager::GetMainVolume() const
{
  const G4VUserDetectorConstruction* vdc = G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  const NuSDDetConstruction* vDet       = static_cast<const NuSDDetConstruction*>(vdc);
  
  return vDet->GetMainVolume();
}
*/




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




