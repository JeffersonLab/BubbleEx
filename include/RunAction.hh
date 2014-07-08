//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren 
// 
//
// this is one of the three sets ( .cc , .hh) of files which we need the 
// correct names for the 
// detectors to be right inorder for correct histogram output.
// these files are used to run, track, and record the particle interactions desired. 
// The stepping file is also used to set perameters in these three sets if needed.
//
// This runaction set here calculates event output to send to histogramss
//
// values which we need to be careful of for output are used here such as EDump.
// need to make sure they point to the correct geometry since it was hardcoded
// to read the g4 geometry

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class HistoManager;

class RunAction : public G4UserRunAction
{
public:
  RunAction(HistoManager*);
  virtual ~RunAction();

  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
    
  void fillPerEvent(G4double, G4double, G4double, G4double); 

private:
  HistoManager* histoManager;

  G4double sumERad, sum2ERad;
  G4double sumEDump, sum2EDump;
    
  G4double sumLRad, sum2LRad;
  G4double sumLDump, sum2LDump;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
