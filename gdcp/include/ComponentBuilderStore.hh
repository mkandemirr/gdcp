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

#ifndef ComponentBuilderStore_hh
#define ComponentBuilderStore_hh 1

#include <vector>
#include <map>

#include "VComponentBuilder.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ComponentBuilderStore : public std::vector<VComponentBuilder*>
{
  public:
    static void Register(VComponentBuilder* pComponent);
    static ComponentBuilderStore* GetInstance();
    static void Clean();

    VComponentBuilder* GetBuilder(const G4String& name, G4bool verbose = true) const;
    inline const std::map<G4String, std::vector<VComponentBuilder*> >& GetMap() const { return fMap; }

    virtual ~ComponentBuilderStore();

    ComponentBuilderStore(const ComponentBuilderStore&) = delete;
    ComponentBuilderStore& operator=(const ComponentBuilderStore&) = delete;

  protected:
    ComponentBuilderStore();

  private:
    static ComponentBuilderStore* fInstance;
    static G4ThreadLocal G4bool locked;

    std::map<G4String, std::vector<VComponentBuilder*> > fMap;
    
};

#endif
