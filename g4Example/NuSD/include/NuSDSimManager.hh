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

#ifndef NuSDSimManager_h
#define NuSDSimManager_h 1

#include "globals.hh"

class NuSDSimManagerMessenger;
class NuSDDetectorBuilder;

class NuSDSimManager
{
  public:
    static NuSDSimManager* GetInstance();
    virtual ~NuSDSimManager();  
  
  private:
    NuSDSimManager();
  
  //UI commands
  public: 
    void SetOpticalPhysicsFlag(G4bool bl) {fIsOpticalPhysicsOn = bl;}
    
  //Getters
  public:
    G4bool IsOpticalPhysicsOn() const {return fIsOpticalPhysicsOn; }
  private:
    static NuSDSimManager *fInstance;  //singleton class
    NuSDSimManagerMessenger *fMessenger;
 
  
    G4bool fIsOpticalPhysicsOn;
    
}; 

#endif
