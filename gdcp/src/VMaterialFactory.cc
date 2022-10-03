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

#include "VMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialFactory::VMaterialFactory()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialFactory::~VMaterialFactory()
{	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* VMaterialFactory::FindOrCreateMaterial(const G4String& name)
{
  
  G4Material* mat = G4NistManager::Instance()->FindOrBuildMaterial(name);
	if(mat) return mat;
  
  //user-defined material
  mat = GetMaterial(name);
  
  //-----------
  if (!mat) 
	{
		std::ostringstream o;
		o << "Material " << name << " not found!";
		G4Exception("VMaterialFactory::GetMaterial","",FatalException,o.str().c_str());
	}
	
	return mat;
       
}





