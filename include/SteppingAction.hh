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
// files to work properly. once define here as long as the pointer here is the 
// same the other 3 set of files dont need to 
// be changed.
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4GDMLParser.hh"
class BCDetectorConstruction;
class EventAction;
class HistoManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(BCDetectorConstruction*, EventAction*, HistoManager*);
  virtual ~SteppingAction();

  void UserSteppingAction(const G4Step*);
 
// set binding to the PV name which will be available when gdml is read
 G4VPhysicalVolume* Radiator;
  G4VPhysicalVolume* ElectronDump;
   G4VPhysicalVolume* Bubble;
    
private:
  BCDetectorConstruction* detector;
  EventAction*          eventaction;
  HistoManager* histoManager;

 
 
 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
