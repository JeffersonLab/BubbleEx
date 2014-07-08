//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//
// needed for sensitivedetector ability. based off g4 example.
//


#ifndef BCSensitiveDetector_h
#define BCSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;

/// Sensitive detector to be attached to the GDML geometry

class BCSensitiveDetector : public G4VSensitiveDetector
{
  public:
      BCSensitiveDetector(const G4String&);
     ~BCSensitiveDetector();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

  private:

};

#endif
