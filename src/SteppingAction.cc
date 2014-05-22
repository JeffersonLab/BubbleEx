//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: SteppingAction.cc 48195 2011-02-02 15:33:39Z jjacquem $
// GEANT4 tag $Name: geant4-09-04 $
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4Step.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det,
			       EventAction* evt, HistoManager* histo)
 :detector(det), eventaction(evt), histoManager(histo) 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step
  G4VPhysicalVolume* volume 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();
      
  if (volume == detector->GetRadiator()) eventaction->AddRad(edep,stepl);
  if (volume == detector->GetElectronDump()) eventaction->AddElectronDump(edep,stepl);
  
  //////

  // Save electrons that leave Radiator

  if (aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) {
    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == detector->GetRadiator()) {
      if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName()== "e-")
	{
	  
	  G4double eelectron = 0.;
	  G4double kinEnergy = 0;
	  G4double telectron = 0.;
	  G4double pelectron = 0.;
	  //  

	  eelectron = aStep->GetPostStepPoint()->GetTotalEnergy();
	  kinEnergy = aStep->GetPostStepPoint()->GetKineticEnergy();

	  telectron = aStep->GetPostStepPoint()->GetMomentumDirection().theta();
	  pelectron = aStep->GetPostStepPoint()->GetMomentumDirection().phi();
	    
	  // fill histograms
	  //
  
	  histoManager->FillHisto(10, eelectron);
	  histoManager->FillHisto(11, kinEnergy);
	  histoManager->FillHisto(12, telectron);
	  histoManager->FillHisto(13, pelectron);
  
	  // fill ntuple
	  //

	  histoManager->FilleNtuple( eelectron, kinEnergy, telectron, pelectron);

	  //	  aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	}
    }
  }

  ////// 

  // Save gammas that enter the Bubble Chamber

  if (aStep->GetPreStepPoint()->GetStepStatus() == fGeomBoundary) {
    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == detector->GetBubble()) {
      if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName()== "gamma")
	{
	  
	  G4double egamma = 0.;
	  G4double tgamma = 0.;
	  G4double pgamma = 0.;
	  //  

	  egamma =  aStep->GetPreStepPoint()->GetTotalEnergy();

	  tgamma = aStep->GetPreStepPoint()->GetMomentumDirection().theta();
	  pgamma = aStep->GetPreStepPoint()->GetMomentumDirection().phi();
	    
	  // fill histograms
	  //
  
	  histoManager->FillHisto(6, egamma);
	  histoManager->FillHisto(7, tgamma);
	  histoManager->FillHisto(8, pgamma);
  
	  // fill ntuple
	  //

	  histoManager->FillgNtuple( egamma, tgamma, pgamma);
	  
	}
    }
  }
  
  //////

  // Print the alpha particle

    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == detector->GetBubble()) {
      if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName()== "alpha")
    	{
    	  G4cout
    	    << "\n--------------------Alpha Particle------------------------------\n"
    	    << "\n Kinetic Energy   : " << G4BestUnit(aStep->GetPreStepPoint()->GetKineticEnergy(),"Energy")
    	    << "\n Step Length      : " << G4BestUnit(aStep->GetStepLength(),"Length")
    	    << "\n Energy Deposited : " << G4BestUnit(aStep->GetTotalEnergyDeposit(),"Energy")
    	    << G4endl;
	  
    	}
    }
    
  //////
   
    // Kill low energy gammas and electrons

      if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName()== "gamma") {
 	if (aStep->GetPreStepPoint()->GetTotalEnergy() < 4.0*MeV) {
	  //	    aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	}
      }

      if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName()== "e-") { 
	if (aStep->GetPreStepPoint()->GetTotalEnergy() < 4.0*MeV) {
	  //	  aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	}
      }

  //////
 
}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
