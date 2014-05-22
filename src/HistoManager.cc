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
// $Id: HistoManager.cc 48195 2011-02-02 15:33:39Z jjacquem $
// GEANT4 tag $Name: geant4-09-04 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

#ifdef G4ANALYSIS_USE
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  :rootFile(0),ntupl(0), Erad(0), Edump(0) ,Lrad(0), Ldump(0), gntupl(0), gEnergy(0), gTheta(0), gPhi(0), entupl(0), eEnergy(0), eKinEnergy(0), eTheta(0), ePhi(0) 
{
      
  // histograms
  for (G4int k=0; k<MaxHisto; k++) histo[k] = 0;
    
  // ntuple
  ntupl = 0;
  gntupl = 0;
  entupl = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
#ifdef G4ANALYSIS_USE  
    if ( rootFile ) delete rootFile;
#endif    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::book()
{ 
#ifdef G4ANALYSIS_USE
 
 // Creating a tree container to handle histograms and ntuples.
 // This tree is associated to an output file.
 //
 G4String fileName = "bubbleEx.root";
 rootFile = new TFile(fileName,"RECREATE");
 if(!rootFile) {
   G4cout << " HistoManager::book :" 
          << " problem creating the ROOT TFile "
          << G4endl;
   return;
 }
   
 histo[1] = new TH1D("1", "Edep in radiator", 150, 0., 15*MeV);
 if (!histo[1]) G4cout << "\n can't create histo 1" << G4endl;
 histo[2] = new TH1D("2", "Edep in dump", 150, 0., 15*MeV);
 if (!histo[2]) G4cout << "\n can't create histo 2" << G4endl;
 histo[3] = new TH1D("3", "trackL in radiator", 100, 0., 10*cm);
 if (!histo[3]) G4cout << "\n can't create histo 3" << G4endl;
 histo[4] = new TH1D("4", "trackL in dump", 100, 0., 10*cm);
 if (!histo[4]) G4cout << "\n can't create histo 4" << G4endl;  

 // create 1 ntuple in subdirectory "tuples"
 //
 ntupl = new TTree("T", "Edep and TrackL");
 ntupl->Branch("Erad", &Erad, "Erad/D");
 ntupl->Branch("Edump", &Edump, "Edump/D");
 ntupl->Branch("Lrad", &Lrad, "Lrad/D");
 ntupl->Branch("Ldump", &Ldump, "Ldump/D");

 gntupl = new TTree("G", "Gamma Distribution");
 gntupl->Branch("gEnergy", &gEnergy, "gEnergy/D");
 gntupl->Branch("gTheta", &gTheta, "gTheta/D");
 gntupl->Branch("gPhi", &gPhi, "gPhi/D");

 histo[6] = new TH1D("6", "Gamma Energy", 150, 0., 15*MeV);
 if (!histo[6]) G4cout << "\n can't create histo 6" << G4endl;
 histo[7] = new TH1D("7", "Gamma Theta", 100, 0., 3*radian);
 if (!histo[7]) G4cout << "\n can't create histo 7" << G4endl;
 histo[8] = new TH1D("8", "Gamma Phi", 100, -1.0, 1*radian);
 if (!histo[8]) G4cout << "\n can't create histo 8" << G4endl;

 entupl = new TTree("E", "Electron Distribution");
 entupl->Branch("eEnergy", &eEnergy, "eEnergy/D");
 entupl->Branch("eKinEnergy", &eKinEnergy, "eKinEnergy/D");
 entupl->Branch("eTheta", &eTheta, "eTheta/D");
 entupl->Branch("ePhi", &ePhi, "ePhi/D");

 histo[10] = new TH1D("10", "Electron Energy", 100, 0., 10*MeV);
 if (!histo[10]) G4cout << "\n can't create histo 10" << G4endl;
 histo[11] = new TH1D("11", "Electron Kinetic Energy", 100, 0., 10*MeV);
 if (!histo[11]) G4cout << "\n can't create histo 11" << G4endl;
 histo[12] = new TH1D("12", "Electron Theta", 100, 0., 3*radian);
 if (!histo[12]) G4cout << "\n can't create histo 12" << G4endl;
 histo[13] = new TH1D("13", "Electron Phi", 100, -1.0, 1.0*radian);
 if (!histo[13]) G4cout << "\n can't create histo 13" << G4endl;

G4cout << "\n----> Histogram file is opened in " << fileName << G4endl;
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::save()
{ 
#ifdef G4ANALYSIS_USE
  if (rootFile) {
    rootFile->Write();       // Writing the histograms to the file
    rootFile->Close();        // and closing the tree (and the file)
    G4cout << "\n----> Histogram Tree is saved \n" << G4endl;
  }
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  if (ih >= MaxHisto) {
    G4cout << "---> warning from HistoManager::FillHisto() : histo " << ih
           << " does not exist. (xbin=" << xbin << " weight=" << weight << ")"
	   << G4endl;
    return;
  }
#ifdef G4ANALYSIS_USE
 if  (histo[ih]) { histo[ih]->Fill(xbin, weight); }
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Normalize(G4int ih, G4double fac)
{
  if (ih >= MaxHisto) {
    G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
           << " does not exist. (fac=" << fac << ")" << G4endl;
    return;
  }
#ifdef G4ANALYSIS_USE
   if (histo[ih]) histo[ih]->Scale(fac);
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillNtuple(G4double EnergyRad, G4double EnergyDump,
                              G4double TrackLRad , G4double TrackLDump )
{
 Erad = EnergyRad;
 Edump = EnergyDump;
 Lrad = TrackLRad;
 Ldump = TrackLDump;

#ifdef G4ANALYSIS_USE
  if (ntupl) ntupl->Fill();
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::PrintStatistic()
{
#ifdef G4ANALYSIS_USE
  if(histo[1]) {
    G4cout << "\n ----> print histograms statistic \n" << G4endl;
    
    G4cout 
    << " ERad : mean = " << G4BestUnit(histo[1]->GetMean(), "Energy") 
            << " rms = " << G4BestUnit(histo[1]->GetRMS(),  "Energy") << G4endl;
    G4cout 	       
    << " EDump : mean = " << G4BestUnit(histo[2]->GetMean(), "Energy") 
            << " rms = " << G4BestUnit(histo[2]->GetRMS(),  "Energy") << G4endl;
    G4cout 
    << " LRad : mean = " << G4BestUnit(histo[3]->GetMean(), "Length") 
            << " rms = " << G4BestUnit(histo[3]->GetRMS(),  "Length") << G4endl;
    G4cout 
    << " LDump : mean = " << G4BestUnit(histo[4]->GetMean(), "Length") 
            << " rms = " << G4BestUnit(histo[4]->GetRMS(),  "Length") << G4endl;

  }
#endif
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillgNtuple(G4double EnergyGamma, G4double ThetaGamma,
                    G4double PhiGamma)
{
  gEnergy = EnergyGamma;
  gTheta = ThetaGamma;
  gPhi = PhiGamma;

#ifdef G4ANALYSIS_USE
  if (gntupl) gntupl->Fill();
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FilleNtuple(G4double EnergyElectron, G4double KinEnergyElectron,
		   G4double ThetaElectron, G4double PhiElectron)
{
  eEnergy = EnergyElectron;
  eKinEnergy = KinEnergyElectron;
  eTheta = ThetaElectron;
  ePhi = PhiElectron;
  
#ifdef G4ANALYSIS_USE
  if (entupl) entupl->Fill();
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::PrintgStatistic()
{
#ifdef G4ANALYSIS_USE
  if(histo[6]) {
    G4cout << "\n ----> print histograms statistic \n" << G4endl;
    
    G4cout 
    << " gEnergy : mean = " << G4BestUnit(histo[6]->GetMean(), "Energy") 
            << " rms = " << G4BestUnit(histo[6]->GetRMS(),  "Energy") << G4endl;
    G4cout 	       
    << " gTheta : mean = " << G4BestUnit(histo[7]->GetMean(), "Theta") 
            << " rms = " << G4BestUnit(histo[7]->GetRMS(),  "Theta") << G4endl;
    G4cout 
    << " gPhi : mean = " << G4BestUnit(histo[8]->GetMean(), "Phi") 
            << " rms = " << G4BestUnit(histo[8]->GetRMS(),  "Phi") << G4endl;
  }
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


