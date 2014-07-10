//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// this is one of the three sets ( .cc , .hh) of files which we need the 
// correct names for the 
// detectors to be right inorder for correct histogram output.
// nothing is defined here which is linked directely however we have secodary 
// or more such as EnergyElectronDump.
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class HistoManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction*, HistoManager*);
  virtual ~EventAction();

  void  BeginOfEventAction(const G4Event*);
  void    EndOfEventAction(const G4Event*);
    
  void AddRad(G4double de, G4double dl) {EnergyRad += de; TrackLRad += dl;};
  void AddElectronDump(G4double de, G4double dl) {EnergyElectronDump += de; TrackLElectronDump += dl;};
    
private:
   RunAction*    runAct;
   HistoManager* histoManager;
      
   G4double  EnergyRad, EnergyElectronDump;
   G4double  TrackLRad, TrackLElectronDump;
                     
   G4int     printModulo;                             
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
