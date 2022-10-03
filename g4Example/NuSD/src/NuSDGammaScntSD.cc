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

#include "NuSDGammaScntSD.hh"
  
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ParticleDefinition.hh" 
#include "G4ParticleTypes.hh"  
#include "G4ProcessType.hh"
//#include "G4NeutronCaptureProcess.hh"
//#include "G4HadronInelasticProcess.hh"
//#include "G4HadronicProcessType.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDGammaScntSD::NuSDGammaScntSD(const G4String& name)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr),
   fHCID{-1}      
{
  
  collectionName.insert("GammaSDHitCol");
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NuSDGammaScntSD::~NuSDGammaScntSD() 
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDGammaScntSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection = new NuSDGammaScntSDHitsCollection(SensitiveDetectorName, collectionName[0]); 

  if(fHCID<0) 
  { 
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
  }

  hce->AddHitsCollection( fHCID, fHitsCollection ); 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool NuSDGammaScntSD::ProcessHits(G4Step* step, G4TouchableHistory* )
{  
  
  /*if u open the below line, neutron will not be tracked since it is uncharged and so it does not deposit energy, 
  so neutron capture in nuScnt by hydrogen will be igonered */
  //if (step->GetTotalEnergyDeposit()==0.) return false; 
  
  G4Track * theTrack = step->GetTrack();

  if( theTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() ) //ignore optic photons dep energy
    return false;

  G4StepPoint *thePreStepPoint  = step->GetPreStepPoint();
  G4int histoDepth = thePreStepPoint->GetTouchable()->GetHistoryDepth(); 
  
  G4int copyNo{};
  //find the copyNo of the UnitPV
  for(G4int depthNo=0;depthNo<=histoDepth;++depthNo)
  {
    if(thePreStepPoint->GetTouchable()->GetVolume(depthNo)->GetName()=="UnitPV")
    {
      copyNo = thePreStepPoint->GetTouchable()->GetVolume(depthNo)->GetCopyNo();
      break;
    }
      
  }

  NuSDGammaScntSDHit *hit  = new NuSDGammaScntSDHit();
  hit->SetCopyNo(copyNo);
  hit->SetParticlePDG(theTrack->GetParticleDefinition()->GetPDGEncoding());
  hit->SetTrackID(theTrack->GetTrackID());
  hit->SetEdep(step->GetTotalEnergyDeposit()*(1./MeV));
  hit->SetTime(step->GetPreStepPoint()->GetGlobalTime()*(1./microsecond));
 
  fHitsCollection->insert(hit);
     
  return true;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDGammaScntSD::EndOfEvent(G4HCofThisEvent*) //works jest before endofEventAction method of eventAction class
{
  
  PrintAll();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NuSDGammaScntSD::PrintAll()
{
 
  G4cout<<"-------------------GammaScntSD Output---------------------------------------"<<G4endl;
  G4cout<<std::left<<std::setw(6+8)<<"CopyNo"<<std::setw(11+8)<<"ParticlePDG"<<std::setw(10+8)<<"TrackID"
        <<std::setw(11+8)<<"Energy(MeV)"<<std::setw(8+8)<<"Time(us)"<<G4endl;

  //G4cout<<std::setprecision(5)<<G4endl;
  
  for ( std::size_t i=0; i<fHitsCollection->entries(); ++i )
  {
    auto hit = (*fHitsCollection)[i];
    
    G4cout<<std::left<<std::setw(6+8)<<hit->GetCopyNo()<<std::setw(11+8)<<hit->GetParticlePDG()<<std::setw(10+8)<<hit->GetTrackID()
          <<std::setw(11+8)<<hit->GetEdep()<<std::setw(8+8)<<hit->GetTime()<<G4endl;
    
  }

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
