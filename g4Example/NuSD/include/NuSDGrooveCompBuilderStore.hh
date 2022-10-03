
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
// NuSDGrooveCompBuilderStore
//
// Class description:
//
// Container for all physical volumes, with functionality derived from
// std::vector<T>. The class is a 'singleton', in that only
// one can exist, and access is provided via the static method
// NuSDGrooveCompBuilderStore::GetInstance()
//
// All volumes should be registered with NuSDGrooveCompBuilderStore, and removed on
// their destruction. The underlying container initially has a capacity of 100.
// A map indexed by volume names is also recorded for fast search;
// pointers to volumes with same name are stored in buckets.
//
// If much additional functionality is added, should consider containment
// instead of inheritance for std::vector<T>.

// 25.07.95, P.Kent, G.Cosmo - Initial version
// --------------------------------------------------------------------
#ifndef NuSDGrooveCompBuilderStore_hh
#define NuSDGrooveCompBuilderStore_hh 1

#include <vector>

#include "NuSDVGrooveCompBuilder.hh"


class NuSDGrooveCompBuilderStore : public std::vector<NuSDVGrooveCompBuilder*>
{
  public:

    static void Register(NuSDVGrooveCompBuilder* pGrooveCompBuilder);
      // Add the volume to the collection.
    //static void DeRegister(NuSDVGrooveCompBuilder* pGrooveCompBuilder);
      // Remove the volume from the collection.
    static NuSDGrooveCompBuilderStore* GetInstance();
      // Get a ptr to the unique store instance, creating it if necessary.
    
    static void Clean();
      // Delete all physical volumes from the store. 


    virtual ~NuSDGrooveCompBuilderStore();
      // Destructor: takes care to delete allocated physical volumes.

    NuSDGrooveCompBuilderStore(const NuSDGrooveCompBuilderStore&) = delete;
    NuSDGrooveCompBuilderStore& operator=(const NuSDGrooveCompBuilderStore&) = delete;
      // Forbidden copy constructor and assignment operator
 
  protected:
    NuSDGrooveCompBuilderStore();

  private:

    static NuSDGrooveCompBuilderStore* fInstance;
    static G4ThreadLocal G4bool locked;

};

#endif
