//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//
// messenger allows for managing communication between the classes. on the 
// header not much has changed except removing and adding pointers. update when 
// sweep magnet and edump are created if commands are needed.
//
// 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef BCDetectorMessenger_h
#define BCDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class BCDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class BCDetectorMessenger: public G4UImessenger
{
  public:
    BCDetectorMessenger(BCDetectorConstruction* );
   ~BCDetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    BCDetectorConstruction* fDetector;

    G4UIdirectory*             BubbleDir;
    G4UIdirectory*             detDir;
    G4UIcmdWithAString        *fTheReadCommand;   
    G4UIcmdWithADoubleAndUnit* MagFieldCmd;
    G4UIcmdWithoutParameter*   UpdateCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
