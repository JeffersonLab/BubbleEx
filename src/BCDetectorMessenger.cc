//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//
// define the messenger here. removed the commands for changes in gui to objects
// as mentioned can recreate so that they will function with the new gdml geo
// but they were originally commented out and didnt seem to be used
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "BCDetectorMessenger.hh"

#include "BCDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BCDetectorMessenger::BCDetectorMessenger( BCDetectorConstruction* Det )
:fDetector(Det)
{ 
// sets directory structure for gui commands we build

  BubbleDir = new G4UIdirectory("/Bubble/");
  BubbleDir->SetGuidance("UI commands of this example");

  detDir = new G4UIdirectory("/Bubble/det/");
  detDir->SetGuidance("detector control");

// for updating geo and mag field 
//  UpdateCmd = new G4UIcmdWithoutParameter("/Bubble/det/update",this);
//  UpdateCmd->SetGuidance("Update geometry.");
//  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
//  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
//  UpdateCmd->AvailableForStates(G4State_Idle);

  MagFieldCmd = new G4UIcmdWithADoubleAndUnit("/Bubble/det/setMagField",this);  
  MagFieldCmd->SetGuidance("Define magnetic field.");
  MagFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
  MagFieldCmd->SetParameterName("Bz",false);
  MagFieldCmd->SetUnitCategory("Magnetic flux density");
  MagFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

// allows for reading file, use in .mac to open our gdml
   fTheReadCommand = new G4UIcmdWithAString("/Bubble/det/readFile", this);
  fTheReadCommand ->SetGuidance("READ GDML file with given name");
  fTheReadCommand ->SetParameterName("FileRead", false);
  fTheReadCommand ->SetDefaultValue("geometry/BubbleMother.gdml");
  fTheReadCommand ->AvailableForStates(G4State_PreInit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BCDetectorMessenger::~BCDetectorMessenger()
{
  delete UpdateCmd;
  delete MagFieldCmd;
  delete fDetector;
  delete fTheReadCommand;  
}

// commands

// sends new file to read 
void BCDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if ( command == fTheReadCommand )
  { 
    fDetector->SetReadFile(newValue);
  }

// if( command == MagFieldCmd )
//   { fDetector->SetMagField(MagFieldCmd->GetNewDoubleValue(newValue));}

  //  if( command == UpdateCmd )
    //   { fDetector->UpdateGeometry(); }
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
