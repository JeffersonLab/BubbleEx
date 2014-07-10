//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
// 
// The stepping file is to set perameters in the eventaction and histomanager 
// sets if needed.
//
// *** here is were we have the link between our geometry and the event tracking
// output.
// this means our geometry needs to be pointed to with correct names in order 
// for the eventaction, runaction, histomanager
// files to work properly. once define here as long as the pointer here is 
// the same the other 3 set of files dont need to 
// be changed.
//
// line 40 starts the point where the volume names are linked to the 
// detectorconstruction.hh file
//
// GetBubble() GetRadiator() GetElectronDump() are all referenced here.
// specifiying the names of the physical volumes in gdml g4 reuses those names.
// otherwise have to use aux with sensedetector or something to make sure 
// binding is correct.
//
// kept same pv names Radiator, Bubble, and ElectronDump (which hasnt been made)
// what is ElectronDump geometry?
//
// GetVolume() gets volumes from gdml now, until gdml file is loaded g4 doesnt 
// radiator is volume so set pointer. only physical volumes we want need to be
// pointed to. other events should track all.
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"

#include "BCDetectorConstruction.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4GDMLParser.hh"

#include "G4LogicalVolume.hh"

#include "G4VPhysicalVolume.hh"

#include "G4PVPlacement.hh"

#include "G4Box.hh"

#include "G4Tubs.hh"

#include "G4PVReplica.hh"

#include "G4ExtrudedSolid.hh"

#include "G4PhysicalVolumeStore.hh"

#include "G4LogicalVolumeStore.hh"

#include "G4SolidStore.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(BCDetectorConstruction* det,
			       EventAction* evt, HistoManager* histo)
 :detector(det), eventaction(evt), histoManager(histo) 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step. below links to bcdetectorconstruction.hh
  // make sure names are correct other wise getradiator() wont work.

  G4VPhysicalVolume* volume 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();

// old      
//  if (volume == detector->GetRadiator()) eventaction->AddRad(edep,stepl);
//  if (volume == detector->GetElectronDump()) eventaction->AddElectronDump(edep,stepl);
// new

  if (volume == Radiator) eventaction->AddRad(edep,stepl);
  if (volume == ElectronDump) eventaction->AddElectronDump(edep,stepl);
  
  //////

  // Save electrons that leave Radiator

  if (aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) {

// original 
//    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == detector->GetRadiator()) {
//     
// new 

    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == Radiator) {
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
// old
//    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == detector->GetBubble()) {
// new
      if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == Bubble) {
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

// old
//    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == detector->GetBubble()) {
    if (aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() == Bubble) {
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
