//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//
// this is one of the three sets ( .cc , .hh) of files which we need 
// the correct names for the detectors to be right inorder for correct 
// histogram output.
// nothing is defined here which is linked directely however we have 
//  secodary or more such as EnergyElectronDump.
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "EventAction.hh"

#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Event.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run, HistoManager* histo)
:runAct(run),histoManager(histo)
{
 printModulo = 1000000; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
  if (evtNb%printModulo == 0) 
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
 
 // initialisation per event
 EnergyRad = EnergyElectronDump = 0.;
 TrackLRad = TrackLElectronDump = 0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
  //accumulates statistic
  //
  runAct->fillPerEvent(EnergyRad, EnergyElectronDump, TrackLRad, TrackLElectronDump);
  

  //fill histograms
  //
  histoManager->FillHisto(1, EnergyRad);
  histoManager->FillHisto(2, EnergyElectronDump);
  histoManager->FillHisto(3, TrackLRad);
  histoManager->FillHisto(4, TrackLElectronDump);
// not sure why these are commented out, were there to begin with.

  //fill ntuple
  //
  //  histoManager->FillNtuple( EnergyRad, EnergyElectronDump, TrackLRad, TrackLElectronDump);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
