//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//
// this is one of the three sets ( .cc , .hh) of files which we need the correct
// names for the 
// detectors to be right inorder for correct histogram output.
// these files are used to run, track, and record the particle interactions desired. 
// The stepping file is also used to set perameters in these three sets if needed.
//
// This runaction set here calculates event output to send to histogramss
//
// values which we need to be careful of for output are used here such as EDump.
// need to make sure they point to the correct geometry since it was hardcoded to read the g4 geometry

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(HistoManager* histo)
:histoManager(histo)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    
  //initialize cumulative quantities
  //
  sumERad = sum2ERad =sumEDump = sum2EDump = 0.;
  sumLRad = sum2LRad =sumLDump = sum2LDump = 0.;
  
  //histograms
  //
  histoManager->book(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::fillPerEvent(G4double ERad, G4double EDump,
                                  G4double LRad, G4double LDump)
{
  //accumulate statistic
  //
  sumERad += ERad;  sum2ERad += ERad*ERad;
  sumEDump += EDump;  sum2EDump += EDump*EDump;
  
  sumLRad += LRad;  sum2LRad += LRad*LRad;
  sumLDump += LDump;  sum2LDump += LDump*LDump;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;
  
  //compute statistics: mean and rms
  //
  sumERad /= NbOfEvents; sum2ERad /= NbOfEvents;
  G4double rmsERad = sum2ERad - sumERad*sumERad;
  if (rmsERad >0.) rmsERad = std::sqrt(rmsERad); else rmsERad = 0.;
  
  sumEDump /= NbOfEvents; sum2EDump /= NbOfEvents;
  G4double rmsEDump = sum2EDump - sumEDump*sumEDump;
  if (rmsEDump >0.) rmsEDump = std::sqrt(rmsEDump); else rmsEDump = 0.;
  
  sumLRad /= NbOfEvents; sum2LRad /= NbOfEvents;
  G4double rmsLRad = sum2LRad - sumLRad*sumLRad;
  if (rmsLRad >0.) rmsLRad = std::sqrt(rmsLRad); else rmsLRad = 0.;
  
  sumLDump /= NbOfEvents; sum2LDump /= NbOfEvents;
  G4double rmsLDump = sum2LDump - sumLDump*sumLDump;
  if (rmsLDump >0.) rmsLDump = std::sqrt(rmsLDump); else rmsLDump = 0.;
  
  //print
  //
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << "\n mean Energy in Radiator : " << G4BestUnit(sumERad,"Energy")
     << " +- "                          << G4BestUnit(rmsERad,"Energy")  
     << "\n mean Energy in Dump      : " << G4BestUnit(sumEDump,"Energy")
     << " +- "                          << G4BestUnit(rmsEDump,"Energy")
     << G4endl;
     
  G4cout
     << "\n mean trackLength in Radiator : " << G4BestUnit(sumLRad,"Length")
     << " +- "                               << G4BestUnit(rmsLRad,"Length")  
     << "\n mean trackLength in Dump      : " << G4BestUnit(sumLDump,"Length")
     << " +- "                               << G4BestUnit(rmsLDump,"Length")
     << "\n------------------------------------------------------------\n"
     << G4endl;
     
  //save histograms
  //
  histoManager->PrintStatistic();
  histoManager->save();   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
