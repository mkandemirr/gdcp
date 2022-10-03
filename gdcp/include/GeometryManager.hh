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

#ifndef GeometryManager_h
#define GeometryManager_h 1

#include "globals.hh"

class VMultiComponentBuilder;

class GeometryManager
{
  public:
    static GeometryManager* GetInstance();
    virtual ~GeometryManager();  
  
  private:
    GeometryManager();
  
  public:
    void SetDetBuilder(VMultiComponentBuilder* detBuilder) {fDetBuilder = detBuilder;}
    VMultiComponentBuilder* GetDetBuilder() const { return fDetBuilder; }

  private:
    static GeometryManager *fInstance;  //singleton class
    VMultiComponentBuilder* fDetBuilder;
    
}; 

#endif
