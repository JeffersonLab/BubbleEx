//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//.....
// this is one of the three sets ( .cc , .hh) of files which we need the correct names for the 
// detectors to be right inorder for correct histogram output.
// these files are used to run, track, and record the particle interactions desired. 
// The stepping file is also used to set perameters in these three sets if needed.
//
// This histomanager set here sets up the output of the events recorded into root histogramss
//
// values which we need to be careful of for output are used here such as EnergyRad.
// need to make sure they point to the correct geometry since it was hardcoded to read the g4 geometry

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 class TFile;
 class TTree;
 class TH1D;

  const G4int MaxHisto = 14;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
  
    HistoManager();
   ~HistoManager();
   
    void book();

    void save();

    void FillHisto(G4int id, G4double bin, G4double weight = 1.0);
    void Normalize(G4int id, G4double fac);    

    void FillNtuple(G4double EnergyRad, G4double EnergyDump,
                    G4double TrackLRad, G4double TrackLDump);

    void FillgNtuple(G4double EnergyGamma, G4double ThetaGamma,
                    G4double PhiGamma);
    
  void FilleNtuple(G4double EnergyElectron, G4double KinEnergyElectron,
		   G4double ThetaElectron, G4double PhiElectron);

  void PrintStatistic();

  void PrintgStatistic();
        
  private:
  
    TFile*   rootFile;
    TH1D*    histo[MaxHisto];            
    TTree*   ntupl; 

    G4double Erad;
    G4double Edump;
    G4double Lrad;
    G4double Ldump;

    TTree*   gntupl; 

    G4double gEnergy;
    G4double gTheta;
    G4double gPhi;

    TTree*   entupl; 

    G4double eEnergy;
    G4double eKinEnergy;
    G4double eTheta;
    G4double ePhi;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
