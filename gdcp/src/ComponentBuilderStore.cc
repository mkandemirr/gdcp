//*******************************************************************************
//* Geant4 Detector Construction Pattern (GDCP) Copyright 2022 Mustafa Kandemir *
//*                                                                             *
//* This file is part of GDCP.                                                  *
//*                                                                             *
//* GDCP is free software: you can redistribute it and/or modify it under the   *
//* terms of the GNU General Public License as published by the Free Software   *
//* Foundation, either version 3 of the License, or any later version.          *                                     
//*                                                                             *
//* GDCP is distributed in the hope that it will be useful, but WITHOUT ANY     *
//* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS   * 
//* FOR A PARTICULAR PURPOSE. See the GNU General Public License for more       * 
//* details.                                                                    *
//*                                                                             *                                         
//* You should have received a copy of the GNU General Public License along     *
//* with GDCP. If not, see <https://www.gnu.org/licenses/>.                     *                                                      
//*******************************************************************************

#include "G4Types.hh"
#include "ComponentBuilderStore.hh"
#include "G4GeometryManager.hh"


#include "G4AutoLock.hh"

namespace
{
  G4Mutex mapMutex = G4MUTEX_INITIALIZER;
}


ComponentBuilderStore* ComponentBuilderStore::fInstance = nullptr;

G4ThreadLocal G4bool ComponentBuilderStore::locked = false;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ComponentBuilderStore::ComponentBuilderStore()
  : std::vector<VComponentBuilder*>()
{
  reserve(100);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ComponentBuilderStore::~ComponentBuilderStore()
{
  Clean(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ComponentBuilderStore::Clean()
{
  
  std::size_t i=0;
  ComponentBuilderStore* store = GetInstance();

  for(auto pos=store->cbegin(); pos!=store->cend(); ++pos)
  {
    G4cout<<"Deleting component buider: "<<(*pos)->GetName()<<" ..."<<G4endl;
    delete *pos; ++i;
  }

  store->fMap.clear(); 
  locked = false;
  store->clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ComponentBuilderStore::Register(VComponentBuilder* pComponent)
{
  ComponentBuilderStore* store = GetInstance();
  store->push_back(pComponent);
  
  const G4String& vol_name = pComponent->GetName();
  auto it = store->fMap.find(vol_name);
  if (it != store->fMap.cend())
  {
    it->second.push_back(pComponent);
  }
  else
  {
    std::vector<VComponentBuilder*> vol_vec { pComponent };
    store->fMap.insert(std::make_pair(vol_name, vol_vec));
  }
 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VComponentBuilder* ComponentBuilderStore::GetBuilder(const G4String& name, G4bool verbose) const
{
  ComponentBuilderStore* store = GetInstance();
  auto pos = store->fMap.find(name);
  
  if(pos != store->fMap.cend())
  {
    if ((verbose) && (pos->second.size()>1))
    {
      std::ostringstream message;
      message << "There exists more than ONE physical volume in store named: "
              << name << "!" << G4endl
              << "Returning the first found.";
      G4Exception("ComponentBuilderStore::GetBuilder()",
                  "GeomMgt1001", JustWarning, message);
    }
    return pos->second[0];
  }
  if (verbose)
  {
     std::ostringstream message;
     message << "Volume NOT found in store !" << G4endl
            << "        Volume " << name << " NOT found in store !" << G4endl
            << "        Returning NULL pointer.";
     G4Exception("ComponentBuilderStore::GetBuilder()",
                 "GeomMgt1001", JustWarning, message);
  }
  return nullptr;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ComponentBuilderStore* ComponentBuilderStore::GetInstance()
{
  static ComponentBuilderStore worldStore;
  if (fInstance == nullptr)
  {
    fInstance = &worldStore;
  }
  return fInstance;
}
