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

#include "NuSDGammaScntSDHit.hh"

G4ThreadLocal G4Allocator<NuSDGammaScntSDHit>* NuSDGammaScntSDHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDGammaScntSDHit::NuSDGammaScntSDHit()
 : G4VHit(),
   fCopyNo{-1},
   fParticlePDG{-1},
   fTrackID{-1},
   fEdep{0.},
   fTime{0.}
   
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDGammaScntSDHit::~NuSDGammaScntSDHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDGammaScntSDHit::NuSDGammaScntSDHit(const NuSDGammaScntSDHit& right)
  : G4VHit()
{
  fCopyNo              = right.fCopyNo;
  fParticlePDG         = right.fParticlePDG;
  fTrackID             = right.fTrackID;
  fEdep                = right.fEdep;
  fTime                = right.fTime; 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const NuSDGammaScntSDHit& NuSDGammaScntSDHit::operator=(const NuSDGammaScntSDHit& right)
{
  fCopyNo              = right.fCopyNo;
  fParticlePDG         = right.fParticlePDG;
  fTrackID             = right.fTrackID;
  fEdep                = right.fEdep;
  fTime                = right.fTime; 
    
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool NuSDGammaScntSDHit::operator==(const NuSDGammaScntSDHit& right) const
{
  return ( this == &right ) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
